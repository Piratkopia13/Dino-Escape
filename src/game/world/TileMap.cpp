#include "TileMap.h"

TileMap::TileMap(std::string filePath)
: m_renderScale(2)
{

	// Set the primitive type
	m_va.setPrimitiveType(sf::Quads);

	// Load the map from file to a string
	std::string rawJson = Utils::readFile(("res/maps/" + filePath).c_str());

	// Create a rapidjson document
	rapidjson::Document doc;
	// Let rapidjson parse the file
	doc.Parse(rawJson.c_str());

	// Store some base map settings
	m_width = doc["width"].GetInt();
	m_height = doc["height"].GetInt();
	m_tileWidth = doc["tilewidth"].GetInt() * m_renderScale;
	m_tileHeight = doc["tileheight"].GetInt() * m_renderScale;

	// Allocate appropriate amount of memory to store collidable tiles	
	m_collisionGrid.resize(m_width, std::vector<bool>(m_height, false)); // False as inital value

	int width = doc["tilewidth"].GetInt() * m_renderScale;
	int height = doc["tileheight"].GetInt() * m_renderScale;

	int numLayers = doc["layers"].Capacity();

	// Loop through all tilesets
	for (rapidjson::Value::ConstValueIterator itr = doc["tilesets"].Begin(); itr != doc["tilesets"].End(); ++itr) {

		// Get the filename of the texture
		const char* texFileName = (*itr)["image"].GetString();

		// Store tileset info
		Tileset tileset;
		tileset.tilesheet.loadFromFile(texFileName);
		tileset.tileWidth = (*itr)["tilewidth"].GetInt();
		tileset.tileHeight = (*itr)["tileheight"].GetInt();
		tileset.tileSpacing = (*itr)["spacing"].GetInt();
		tileset.imgWidth = (*itr)["imagewidth"].GetInt();
		tileset.imgHeight = (*itr)["imageheight"].GetInt();
		tileset.firstgid = (*itr)["firstgid"].GetInt();
		tileset.lastgid = tileset.firstgid + (*itr)["tilecount"].GetInt();

		// Store which tiles are collidable
		if (itr->HasMember("tileproperties") && (*itr)["tileproperties"].IsObject()) {
			for (rapidjson::Value::ConstMemberIterator mem = (*itr)["tileproperties"].MemberBegin(); mem != (*itr)["tileproperties"].MemberEnd(); ++mem) {
				if (mem->value.HasMember("collidable")
					&& strcmp(mem->value.FindMember("collidable")->value.GetString(), "1") == 0) {
					tileset.collidableTiles.insert({ atoi(mem->name.GetString()) + 1, true });
				}
			}
		}

		// Add tileset to the array (Useless atm since it cant handle more then one anyway)
		m_tilesets.push_back(tileset);

	}

	// Loop through all layers
	for (rapidjson::Value::ConstValueIterator itr = doc["layers"].Begin(); itr != doc["layers"].End(); ++itr) {

		// Make sure its a tile layer and not an object layer
		if (itr->HasMember("data")) {

			// Loop through all tiles
			for (int x = m_width - 1; x >= 0; x--) {
				for (int y = m_height - 1; y >= 0; y--) {

					unsigned int gid = (*itr)["data"][(x + y*m_width)].GetInt(); // 64

					// Find the correct tileset
					Tileset &curSet = m_tilesets.front();
					for (auto &tileset : m_tilesets) {
						if (gid >= tileset.firstgid && gid <= tileset.lastgid) {
							curSet = tileset;
							break;
						}
					}

					// Add cell to the collision grid
					if (!m_collisionGrid[x][y]) {
						m_collisionGrid[x][y] = (curSet.collidableTiles.count(gid)) ? true : false;
					}

					// If the tile is not empty
					if (gid != 0) {

						// Calculate stuffs

						int tileGid = gid - curSet.firstgid; // Subtract firstgid to get the relative gid to this set

						float texX = (tileGid % (curSet.imgWidth / curSet.tileWidth)) // Gets the column
							* static_cast<float>(curSet.tileWidth / static_cast<float>(curSet.imgWidth));		  // Converts the column to accual coordinates

						float texY = ceilf(static_cast<float>(static_cast<unsigned int>(tileGid / (curSet.imgWidth / curSet.tileWidth)))) // Gets the row
							* static_cast<float>(curSet.tileHeight / static_cast<float>(curSet.imgHeight));		   // Converts the row to accual coordinates

						float tileHeight = curSet.tileHeight / static_cast<float>(curSet.imgHeight); // Tile height in pixels
						float tileWidth = curSet.tileWidth / static_cast<float>(curSet.imgWidth);	// Tile width in pixels

						sf::Vertex vert;

						// Add .1 pixels to avoid artifacts when scrolling

						vert.position = sf::Vector2f(static_cast<float>(x) * width + width, static_cast<float>(y) * height + height);
						vert.texCoords = sf::Vector2f((texX + tileWidth) * curSet.imgWidth, (texY + tileHeight) * curSet.imgHeight) + sf::Vector2f(-.1f, -.1f);
						m_va.append(vert);

						vert.position = sf::Vector2f(static_cast<float>(x) * width + width, static_cast<float>(y) * height);
						vert.texCoords = sf::Vector2f((texX + tileWidth) * curSet.imgWidth, texY * curSet.imgHeight) + sf::Vector2f(-.1f, .1f);
						m_va.append(vert);

						vert.position = sf::Vector2f(static_cast<float>(x) * width, static_cast<float>(y) * height);
						vert.texCoords = sf::Vector2f(texX * curSet.imgWidth, texY * curSet.imgHeight) + sf::Vector2f(.1f, .1f);
						m_va.append(vert);

						vert.position = sf::Vector2f(static_cast<float>(x) * width, static_cast<float>(y) * height + height);
						vert.texCoords = sf::Vector2f(texX * curSet.imgWidth, (texY + tileHeight) * curSet.imgHeight) + sf::Vector2f(.1f, -.1f);
						m_va.append(vert);

					}
				}
			}

		}


		// If map has objects
		if (itr->HasMember("objects") && (*itr)["objects"].IsArray()) {
			auto &objects = (*itr)["objects"];
			// Check objects for properties
			for (rapidjson::Value::ConstValueIterator obj = objects.Begin(); obj != objects.End(); ++obj) {
				
				// Create the object
				struct Object object;
				object.name = (*obj)["name"].GetString();
				object.type = (*obj)["type"].GetString();
				object.x = static_cast<float>((*obj)["x"].GetDouble()) * m_renderScale;
				object.y = static_cast<float>((*obj)["y"].GetDouble()) * m_renderScale;
				object.width = static_cast<float>((*obj)["width"].GetDouble()) * m_renderScale;
				object.height = static_cast<float>((*obj)["height"].GetDouble()) * m_renderScale;

				// Loop through all properties
				for (rapidjson::Value::ConstMemberIterator prop = (*obj)["properties"].MemberBegin(); prop != (*obj)["properties"].MemberEnd(); ++prop)
					object.properties.push_back({prop->name.GetString(), prop->value.GetString()});

				// Add the object
				m_objects.push_back(object);

			}
		}


	}

}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// Set the texture to the tilesheet
	states.texture = &m_tilesets.back().tilesheet;
	// Draw the map from the vertex array
	target.draw(m_va, states);

}

sf::Vector2f TileMap::resolveCollisions(Entity& entity) {

	sf::Vector2f diff;
	sf::Vector2f vel;

	// Move the entity back on the y-axis to only check for x collisions
	entity.getTransformable().move(sf::Vector2f(0, -entity.getVelocity().y));

	// Get the entities bounding box
	sf::FloatRect bb = entity.getGlobalBounds();
	// Get the distance between the center of the bb and the distance of the tile it collided with
	// Will be 0 if there was no collision
	diff = getCollisionOverlap(bb);

	// If there was a collision
	if (diff.x != 0.0f) {

		// Move the entity back to the left if it was moving right
		if (entity.getVelocity().x > 0)
			vel.x = diff.x - m_tileWidth / 2.0f - bb.width / 2.0f - 0.1f;

		// Move the entity back to the right if it was moving left
		if (entity.getVelocity().x < 0)
			vel.x = diff.x + m_tileWidth / 2.0f + bb.width / 2.0f + 0.1f;
	}

	// Move the entity back on the x-axis to only check for y collisions
	entity.getTransformable().move(sf::Vector2f(-entity.getVelocity().x, entity.getVelocity().y));
	// Get the distance between the center of the bb and the distance of the tile it collided with
	// Will be 0 if there was no collision
	diff = getCollisionOverlap(entity.getGlobalBounds());

	// If there was a collision
	if (diff.y != 0.0f) {

		// Move the entity back up if it was moving down
		if (entity.getVelocity().y > 0)
			vel.y = diff.y - m_tileHeight / 2.0f - bb.height / 2.0f - 0.1f;

		// Move the entity back down if it was moving up
		if (entity.getVelocity().y < 0)
			vel.y = diff.y + m_tileHeight / 2.0f + bb.height / 2.0f + 0.1f;

	}
	entity.getTransformable().move(sf::Vector2f(entity.getVelocity().x, 0));


	// Make sure the values arent too small and unnecessary to calculate
	if (fabs(vel.x) < 0.0001f) vel.x = 0.f;
	if (fabs(vel.y) < 0.0001f) vel.y = 0.f;

	// Return a vector that the entity needs to move by to get out of the collision
	return vel;

}

sf::Vector2f TileMap::getCollisionOverlap(sf::FloatRect bb) {

	ADD_DEBUG_SHAPE_IF_ENABLED(bb, sf::Color::Blue);

	std::vector<sf::FloatRect> tiles;
	// Get all tiles that the player could possibly collide with on from its current position and size
	getCollidableTilesFor(bb, tiles);

	// Loop through all tiles
	for (auto& tile : tiles) {

		ADD_DEBUG_SHAPE_IF_ENABLED(tile, sf::Color::Green);

		// Check for a collision
		if (tile.intersects(bb)) {

			// Return distance between the collided tile's center and the player's center

			sf::Vector2f velBack;
			velBack.x = (tile.left + (tile.width / 2.0f)) - (bb.left + (bb.width / 2.0f));
			velBack.y = (tile.top + (tile.height / 2.0f)) - (bb.top + (bb.height / 2.0f));

			return velBack;

		}
	}

	// No tiles intersected, return 0
	return sf::Vector2f(0.f, 0.f);

}

void TileMap::getCollidableTilesFor(const sf::FloatRect& rect, std::vector<sf::FloatRect>& out) const {

	// Make sure the rect is on the map
	if (!rect.intersects(getBounds()))
		return;

	// Convert the FloatRect's coordinates and size to grid coordinates to loop
	unsigned int xStart = static_cast<int>((rect.left * m_width)				/ (m_width	* m_tileWidth));
	unsigned int yStart = static_cast<int>((rect.top * m_height)				/ (m_height * m_tileHeight));
	unsigned int xEnd = static_cast<int> (((rect.left + rect.width)	* m_width)	/ (m_width	* m_tileWidth));
	unsigned int yEnd = static_cast<int> (((rect.top + rect.height)	* m_height) / (m_height * m_tileHeight));

	// Make sure no cell is outside the grid
	(xStart < 0) ? xStart = 0 : xStart;
	(yStart < 0) ? yStart = 0 : yStart;
	(xEnd > m_width - 1) ? xEnd = m_width - 1 : xEnd;
	(yStart > m_height - 1) ? yStart = m_height - 1 : yStart;
	(yEnd > m_height - 1) ? yEnd = m_height - 1 : yEnd;

	// Check for collisions
	for (unsigned int y = yStart; y <= yEnd; y++) {
		for (unsigned int x = xStart; x <= xEnd; x++) {
			// Check if the tile is collidable
			if (m_collisionGrid[x][y])
				// Add the tile to the output
				out.push_back(sf::FloatRect(static_cast<float>(x * m_tileWidth), static_cast<float>(y * m_tileHeight),
					static_cast<float>(m_tileWidth), static_cast<float>((m_tileHeight))));
		}
	}

}

bool TileMap::isPointColliding(const sf::Vector2f& point) const {

	// Make sure the point is not outside the map
	if (point.x < 0 || point.y < 0)
		return false;

	// Get the grid coordinates of the point
	unsigned int x = static_cast<unsigned int>((point.x * m_width) / (m_width	* m_tileWidth));
	unsigned int y = static_cast<unsigned int>((point.y * m_height) / (m_height * m_tileHeight));

	// Make sure the point is not outside the map
	if (x >= m_width || y >= m_height)
		return false;

	// Return true if the tile is collidable
	return m_collisionGrid[x][y];

}

bool TileMap::isLineColliding(const sf::Vector2f& start, const sf::Vector2f& end) {

	unsigned int x  = static_cast<unsigned int>(start.x	/ m_tileWidth);
	unsigned int x2 = static_cast<unsigned int>(end.x		/ m_tileWidth);
	unsigned int y  = static_cast<unsigned int>(start.y	/ m_tileWidth);
	unsigned int y2 = static_cast<unsigned int>(end.y		/ m_tileWidth);

	// Uses Bresenham's line algorithm

	int w = x2 - x;
	int h = y2 - y;
	int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
	if (w < 0) dx1 = -1; else if (w>0) dx1 = 1;
	if (h < 0) dy1 = -1; else if (h>0) dy1 = 1;
	if (w < 0) dx2 = -1; else if (w>0) dx2 = 1;
	int longest = abs(w);
	int shortest = abs(h);
	if (!(longest > shortest)) {
		longest = abs(h);
		shortest = abs(w);
		if (h < 0) dy2 = -1; else if (h>0) dy2 = 1;
		dx2 = 0;
	}
	int numerator = longest >> 1;
	for (int i = 0; i <= longest; i++) {
		
#ifdef ENABLE_DEBUG_RAYS
		DebugRenderer::addShape(sf::Vector2f(x * m_tileWidth, y * m_tileHeight), sf::Vector2f(m_tileWidth, m_tileHeight), sf::Color::Magenta);
#endif

		if (x < m_width && y < m_height)
			if (m_collisionGrid[x][y])
				// collision found, return true!
				return true;

		numerator += shortest;
		if (!(numerator < longest)) {
			numerator -= longest;
			x += dx1;
			y += dy1;
		} else {
			x += dx2;
			y += dy2;
		}
	}

	// No collision was found
	return false;

}

sf::FloatRect TileMap::getBounds() const {
	return sf::FloatRect(0.f, 0.f, static_cast<float>(m_width * m_tileWidth), static_cast<float>(m_height * m_tileHeight));
}

const std::vector<TileMap::Object>& TileMap::getObjects() const {
	return m_objects;
}