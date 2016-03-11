#include "DebugRenderer.h"

#ifdef ENABLE_DEBUG_SHAPES

// Initialize the static list
std::vector<sf::RectangleShape> DebugRenderer::m_shapes;

void DebugRenderer::addShape(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& color, const bool onlyBorder) {

	// Create a new shape
	sf::RectangleShape shape;
	// Set the position and size
	shape.setPosition(pos);
	shape.setSize(size);

	// Set up color and border
	if (onlyBorder) {
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(color);
		shape.setOutlineThickness(-1.f);
	} else {
		shape.setFillColor(color);
	}

	// Add the shape to be rendered
	m_shapes.push_back(shape);
}

void DebugRenderer::addShape(const sf::Vector2f& centerPos, const sf::FloatRect& bounds, const sf::Color& color, const bool onlyBorder) {

	// Get the size of the shape from the bounds
	sf::Vector2f size(bounds.width, bounds.height);
	// Calculate the position of the shape from the bounds
	sf::Vector2f pos = centerPos;
	pos.x -= size.x / 2.0f;
	pos.y -= size.y / 2.0f;

	addShape(pos, size, color, onlyBorder);

}

void DebugRenderer::addShape(const sf::FloatRect& bounds, const sf::Color& color, const bool onlyBorder) {

	// Get the position of the shape from the bounds
	sf::Vector2f pos(bounds.left, bounds.top);
	// Get the size of the shape from the bounds
	sf::Vector2f size(bounds.width, bounds.height);

	addShape(pos, size, color, onlyBorder);

}

void DebugRenderer::draw(sf::RenderTarget& target) {

	// Draw all shapes
	for (auto s : m_shapes)
		target.draw(s);

}

void DebugRenderer::reset() {
	// Clear the list
	m_shapes.clear();
}

#endif