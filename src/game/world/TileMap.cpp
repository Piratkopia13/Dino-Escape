#include "TileMap.h"

TileMap::TileMap(std::string filePath) {

	m_va.setPrimitiveType(sf::PrimitiveType::Quads);

	// Load map from json file
	std::string rawJson = Utils::readFile(("res/maps/" + filePath).c_str());

	rapidjson::Document doc;
	doc.Parse(rawJson.c_str());

	m_width = doc["width"].GetInt();
	m_height = doc["height"].GetInt();
	m_tileWidth = doc["tilewidth"].GetInt() * m_renderScale;
	m_tileHeight = doc["tileheight"].GetInt() * m_renderScale;

	// Allocate appropriate amount of memory to store collidable tiles	
	m_collisionGrid.resize(m_width, std::vector<bool>(m_height, false)); // False as inital value

	int width = doc["tilewidth"].GetInt() * m_renderScale;
	int height = doc["tileheight"].GetInt() * m_renderScale;

	int numLayers = doc["layers"].Capacity();

	// TODO: Change these to vectors
	//GLfloat* vertices = (GLfloat*)malloc(sizeof(GLfloat) * m_width*m_height * 8 * numLayers); // 8 vertices per tile
	//GLuint*  indices = (GLuint*)malloc(sizeof(GLuint)  * m_width*m_height * 6 * numLayers); // 6 indices per tile
	//GLfloat* texCoords = (GLfloat*)malloc(sizeof(GLfloat) * m_width*m_height * 8 * numLayers); // 8 texcoords per tile
	//int vertCount = 0;
	//int indCount = 0;
	//int texCount = 0;

	// Load tileset textures
	for (rapidjson::Value::ConstValueIterator itr = doc["tilesets"].Begin(); itr != doc["tilesets"].End(); ++itr) {

		const char* texFileName = (*itr)["image"].GetString();

		// Store tileset info
		Tileset tileset;
		tileset.tilesheet.loadFromFile(texFileName);
		//tileset.tilesheet.loadFromFile("res/textures/test.png");
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
					//std::cout << "Added " << mem->name.GetString() << " to collidables" << std::endl;
					tileset.collidableTiles.insert({ atoi(mem->name.GetString()) + 1, true });
				}
			}
		}

		// Add tileset to the array (Useless atm since it cant handle more then one anyway)
		m_tilesets.push_back(tileset);

	}

	// TODO: Minor fix for: Layers with data on same tile both renders if opacity is full

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
				object.x = (*obj)["x"].GetDouble() * m_renderScale;
				object.y = (*obj)["y"].GetDouble() * m_renderScale;
				object.width = (*obj)["width"].GetDouble() * m_renderScale;
				object.height = (*obj)["height"].GetDouble() * m_renderScale;

				// Loop through all properties
				for (rapidjson::Value::ConstMemberIterator prop = (*obj)["properties"].MemberBegin(); prop != (*obj)["properties"].MemberEnd(); ++prop)
					object.properties.push_back({prop->name.GetString(), prop->value.GetString()});

				// Add the object
				m_objects.push_back(object);

			}
		}


	}

}

TileMap::~TileMap() {
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(m_va, &m_tilesets.back().tilesheet);

}

sf::Vector2f TileMap::resolveCollisions(Entity& entity) {

	//std::cout << "Resolve collision " << entity.velocity.x << ", " << entity.velocity.y << std::endl;

	sf::Vector2f diff;
	sf::Vector2f vel;

	entity.getTransformable().move(sf::Vector2f(0, -entity.getVelocity().y));

	sf::FloatRect bb = entity.getGlobalBounds();
	diff = getCollisionOverlap(bb);
	if (diff.x != 0.0f) {

		if (entity.getVelocity().x > 0)
			vel.x = diff.x - m_tileWidth / 2.0f - bb.width / 2.0f - 0.1f;

		if (entity.getVelocity().x < 0)
			vel.x = diff.x + m_tileWidth / 2.0f + bb.width / 2.0f + 0.1f;
	}

	entity.getTransformable().move(sf::Vector2f(-entity.getVelocity().x, entity.getVelocity().y));
	diff = getCollisionOverlap(entity.getGlobalBounds());
	if (diff.y != 0.0f) {

		// If moving down
		if (entity.getVelocity().y > 0)
			vel.y = diff.y - m_tileHeight / 2.0f - bb.height / 2.0f - 0.1f;
		// If moving up
		if (entity.getVelocity().y < 0)
			vel.y = diff.y + m_tileHeight / 2.0f + bb.height / 2.0f + 0.1f;

	}
	entity.getTransformable().move(sf::Vector2f(entity.getVelocity().x, 0));


	// Make sure the values arent too small
	if (fabs(vel.x) < 0.0001f) vel.x = 0.f;
	if (fabs(vel.y) < 0.0001f) vel.y = 0.f;

	return vel;


}

sf::Vector2f TileMap::getCollisionOverlap(sf::FloatRect bb) {

#ifdef ENABLE_DEBUG_SHAPES
	DebugRenderer::addShape(bb, sf::Color::Blue);
#endif

	std::vector<sf::FloatRect> tiles;
	getCollidableTilesFor(bb, tiles);

	for (sf::FloatRect tile : tiles) {

#ifdef ENABLE_DEBUG_SHAPES
		DebugRenderer::addShape(tile, sf::Color::Green);
#endif

		if (tile.intersects(bb)) {

			// WE HAVE A COLLISION!!

			//std::cout << "Collision" << std::endl;

			// Return distance between the collided tile's center and the player's center

			sf::Vector2f velBack;
			velBack.x = (tile.left + (tile.width / 2.0f)) - (bb.left + (bb.width / 2.0f));
			velBack.y = (tile.top + (tile.height / 2.0f)) - (bb.top + (bb.height / 2.0f));

			return velBack;

		}
	}

	return sf::Vector2f(0, 0);

}

void TileMap::getCollidableTilesFor(const sf::FloatRect& rect, std::vector<sf::FloatRect>& out) const {

	// Make sure the rect is on the map
	if (!rect.intersects(getBounds()))
		return;

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

	/*std::cout << xStart << ", " << xEnd << std::endl;
	std::cout << yStart << ", " << yEnd << std::endl << std::endl;*/

	// Check for collisions
	for (unsigned int y = yStart; y <= yEnd; y++) {
		for (unsigned int x = xStart; x <= xEnd; x++) {
			if (m_collisionGrid[x][y]) // If maptile is collidable
				out.push_back(sf::FloatRect(static_cast<float>(x * m_tileWidth), static_cast<float>(y * m_tileHeight),
					static_cast<float>(m_tileWidth), static_cast<float>((m_tileHeight))));
		}
	}


	return;

}

bool TileMap::isPointColliding(const sf::Vector2f& point) const {

	if (point.x < 0 || point.y < 0)
		return false;

	unsigned int x = static_cast<unsigned int>((point.x * m_width) / (m_width	* m_tileWidth));
	unsigned int y = static_cast<unsigned int>((point.y * m_height) / (m_height * m_tileHeight));

	if (x >= m_width || y >= m_height)
		return false;

	return m_collisionGrid[x][y]; // If maptile is collidable

}

bool TileMap::isLineColliding(const sf::Vector2f& start, const sf::Vector2f& end) {

	unsigned int x  = static_cast<unsigned int>(start.x	/ m_tileWidth);
	unsigned int x2 = static_cast<unsigned int>(end.x		/ m_tileWidth);
	unsigned int y  = static_cast<unsigned int>(start.y	/ m_tileWidth);
	unsigned int y2 = static_cast<unsigned int>(end.y		/ m_tileWidth);


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
			if (m_collisionGrid[x][y]) return true; // collision found, return true!

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

	return false;

}

sf::FloatRect TileMap::getBounds() const {
	return sf::FloatRect(0, 0, m_width * m_tileWidth, m_height * m_tileHeight);
}

const std::vector<TileMap::Object>& TileMap::getObjects() const {

	return m_objects;
}