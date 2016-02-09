#pragma once

#include <SFML\Graphics.hpp>

class Camera {

public:
	Camera(sf::RenderWindow& window);

	void handleResize(sf::Event::SizeEvent size);

	void setConstraints(sf::FloatRect& constraints);

	void moveTo(const sf::Vector2f& position);

private:
	void updateView();

private:
	sf::View m_view;
	sf::RenderWindow& m_window;
	sf::FloatRect m_constraints;

};

