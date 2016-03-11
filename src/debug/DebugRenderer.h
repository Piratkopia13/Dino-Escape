#pragma once

#include "../Common.h"

#ifdef ENABLE_DEBUG_SHAPES

#include <vector>

// Debug class
// Allows easy rendering for RectangleShapes
// Can be used to show bounding boxes, etc.
class DebugRenderer {

public:
	// Add a new shape to render
	static void addShape(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& color, const bool onlyBorder = true);
	static void addShape(const sf::Vector2f& centerPos, const sf::FloatRect& bounds, const sf::Color& color, const bool onlyBorder = true);
	static void addShape(const sf::FloatRect& bounds, const sf::Color& color, const bool onlyBorder = true);

	// Draw all the shapes
	static void draw(sf::RenderTarget& target);

	// Clears all shapes from the render list
	static void reset();
	
private:
	// List of shapes to render
	static std::vector<sf::RectangleShape> m_shapes;

};

#endif