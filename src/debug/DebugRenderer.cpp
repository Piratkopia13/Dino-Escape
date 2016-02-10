#include "DebugRenderer.h"

std::vector<sf::RectangleShape> DebugRenderer::m_shapes;

void DebugRenderer::addShape(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& color, const bool onlyBorder) {

	sf::RectangleShape shape;
	shape.setPosition(pos);
	shape.setSize(size);

	if (onlyBorder) {
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(color);
		shape.setOutlineThickness(-1.f);
	} else {
		shape.setFillColor(color);
	}

	m_shapes.push_back(shape);
}

void DebugRenderer::addShape(const sf::Vector2f& centerPos, const sf::FloatRect& bounds, const sf::Color& color, const bool onlyBorder) {

	sf::Vector2f pos = centerPos;
	sf::Vector2f size(bounds.width, bounds.height);
	pos.x -= size.x / 2.0f;
	pos.y -= size.y / 2.0f;

	addShape(pos, size, color, onlyBorder);

}

void DebugRenderer::draw(sf::RenderTarget& target) {

	for (auto s : m_shapes) {
		target.draw(s);
	}

	m_shapes.clear();

}