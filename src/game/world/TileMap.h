#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include <rapidjson\document.h>
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

#include <SFML\Graphics.hpp>

#include "../../Utils.h"
#include "../world/Entity.h"
#include "../../debug/DebugRenderer.h"

class TileMap : public sf::Drawable {

public:
	struct Property {
		std::string name;
		std::string value;
	};
	struct Object {
		float height, width;
		float x, y;
		std::string name;
		std::vector<TileMap::Property> properties;
	};

public:
	TileMap(std::string filePath);
	~TileMap();
	
	// Renders the map using its own Vertex Array
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Resolves collision between this map and the entity
	sf::Vector2f resolveCollisions(Entity& entity);
	// Returns the distance between the FloatRect's center and the tile's center on collision
	sf::Vector2f getCollisionOverlap(sf::FloatRect bb);
	// Returns a list of all tiles that set FloatRect could possibly collide with
	std::vector<sf::FloatRect> getCollidableTilesFor(const sf::FloatRect& rect) const;

	// Returns true if set point is colliding with a tile
	bool isPointColliding(const sf::Vector2f& point) const;

	// Returns true if set line is colliding with a tile
	// Uses Bresenham's line algorithm
	bool isLineColliding(const sf::Vector2f& start, const sf::Vector2f& end);

	// Returns the max bounds for the map
	sf::FloatRect getBounds() const;

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

	const int m_renderScale = 2;
	

};