#pragma once

#include <SFML\Graphics.hpp>

class Camera {

public:
	Camera(sf::RenderWindow& window);

	void update(sf::Time dt);
	void handleResize(sf::Event::SizeEvent size);

	void moveTo(const sf::Vector2f& position);

private:
	void updateView();

private:
	sf::View m_view;
	sf::RenderWindow& m_window;

};

