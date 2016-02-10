#pragma once

#include <vector>

#include <SFML\Graphics.hpp>

class DebugRenderer {

public:
	static void addShape(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& color, const bool onlyBorder = true);
	static void addShape(const sf::Vector2f& centerPos, const sf::FloatRect& bounds, const sf::Color& color, const bool onlyBorder = true);

	static void draw(sf::RenderTarget& target);
	
private:
	static std::vector<sf::RectangleShape> m_shapes;

};