#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <rapidjson\document.h>
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

#include <SFML\Graphics.hpp>

#include <vector>

#include "Utils.h"
#include "Entity.h"

class TileMap : public sf::Drawable {

public:
	TileMap(std::string filePath);
	~TileMap();
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f resolveCollisions(Entity& entity);
	sf::Vector2f getCollisionOverlap(sf::FloatRect bb);
	std::vector<sf::FloatRect> getCollidableTilesFor(const sf::FloatRect& rect) const;

	bool isPointColliding(const sf::Vector2f& point) const;
	bool isLineColliding(const sf::Vector2f& start, const sf::Vector2f& end);

	std::vector<sf::RectangleShape> debugShapes;

private:

	sf::VertexArray m_va;

	struct Tileset {
		sf::Texture tilesheet;
		unsigned int firstgid, lastgid;
		unsigned int tileWidth, tileHeight, tileSpacing;
		unsigned int imgWidth, imgHeight;
		std::map<unsigned int, bool> collidableTiles;
	};

	unsigned int m_width, m_height;
	unsigned int m_tileWidth, m_tileHeight;
	std::vector<Tileset> m_tilesets;

	std::vector< std::vector<bool> >* m_collisionGrid;

	const float m_renderScale = 2.0f;


};