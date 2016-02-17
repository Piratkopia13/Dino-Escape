#pragma once

#include <SFML\Graphics.hpp>

class Camera {

public:
	Camera(sf::RenderWindow& window);

	void handleResize(sf::Event::SizeEvent size);
	void moveTo(const sf::Vector2f& position);
	void setConstraints(sf::FloatRect& constraints);
	void zoom(float zoom);
	const sf::View& getView() const;
	void applyView();

private:
	void checkSize();

private:
	sf::View m_view;
	sf::RenderWindow& m_window;
	sf::FloatRect m_constraints;
	float m_zoom;
	bool m_hasConstraints;
	sf::Vector2f m_center;

};

