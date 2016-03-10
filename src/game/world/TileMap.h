#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <rapidjson\document.h>
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

#include <SFML\Graphics.hpp>

#include "../../Utils.h"
#include "../world/Entity.h"
#include "../../debug/DebugRenderer.h"

// A drawable TileMap
// Loads from a json file exported from the Tiled editor (http://www.mapeditor.org/)
// Uses the rapidjson library for parsing of the file
// Note: currenly limitations are as follows:
//		 Can only handle one tileset
//		 The tileset must be defined in the json file, not in an external .tmx
// Creation of maps:
//		Mark tiles with the property "collidable" and a value of "1" to make them collidable in the game
//		Spawnpoints are defined by an object with the type "Spawn" and a name of either "Player" or an enemy "Effie" or "Blobber"
//		Spawnpoints can have a property "Facing" with a value of "left" or "right" which will define what direction the entity will face on spawn
//		Only the position of spawnpoints are taken into account
//		Areas where entities will take damage can be defined by objects with the name "DamageArea"
//		Damage area objects can have a property named "Damage" with a value of how much damage entites should take while in it (default is 1)
//		The map goal is defined by an object named "Goal"
class TileMap : public sf::Drawable {

public:
	// A tile or object property
	struct Property {
		std::string name;
		std::string value;
	};
	// An object
	struct Object {
		float height, width;
		float x, y;
		std::string name;
		std::string type;
		std::vector<TileMap::Property> properties;
	};

public:
	// Creates a map from the specified path to a Tiled json file
	TileMap(std::string filePath);
	
	// Renders the map
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Resolves collision between this map and the entity
	sf::Vector2f resolveCollisions(Entity& entity);
	// Returns the distance between the FloatRect's center and the tile's center on collision
	sf::Vector2f getCollisionOverlap(sf::FloatRect bb);
	// Outputs a list of all tiles that set FloatRect could possibly collide with
	void getCollidableTilesFor(const sf::FloatRect& rect, std::vector<sf::FloatRect>& out) const;

	// Returns true if set point is colliding with a tile
	bool isPointColliding(const sf::Vector2f& point) const;

	// Returns true if set line is colliding with a tile
	// Uses Bresenham's line algorithm
	bool isLineColliding(const sf::Vector2f& start, const sf::Vector2f& end);

	// Returns the max bounds for the map
	sf::FloatRect getBounds() const;

	// Returns a reference to all objects defined on the map
	const std::vector<TileMap::Object>& getObjects() const;

private:

	// Vertex Array to store vertices and texture coordinates for efficient rendering
	sf::VertexArray m_va;

	// All info needed for a tileset (Only one tileset is supported atm)
	struct Tileset {
		sf::Texture tilesheet;
		unsigned int firstgid, lastgid;
		unsigned int tileWidth, tileHeight, tileSpacing;
		unsigned int imgWidth, imgHeight;
		std::map<unsigned int, bool> collidableTiles;
	};
	// List of all tilesets (Only one tileset is supported atm)
	std::vector<struct Tileset> m_tilesets;

	// List of all objects on the map
	std::vector<TileMap::Object> m_objects;

	// Number of tiles in each direction
	unsigned int m_width, m_height;
	// Tile size in pixels
	unsigned int m_tileWidth, m_tileHeight;

	// 2D vector to store which tiles are collidable
	std::vector< std::vector<bool> > m_collisionGrid;

	// What scale the tiles should be rendered in
	const int m_renderScale;
	

};