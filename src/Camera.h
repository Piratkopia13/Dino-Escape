#pragma once

#include <SFML\Graphics.hpp>

class Camera {

public:
	Camera(const sf::RenderWindow& window);

	// Resizes the viewport to the new aspect ratio
	void handleResize(const sf::Event::SizeEvent& size);
	// Interpolates and moves the camera to the specified position
	void moveTo(const sf::Vector2f& position);

	// Sets contraints that the camera always will be inside
	void setConstraints(const sf::FloatRect& constraints);
	// Locks the width to the set amount, height is adjusted depending on aspect ratio
	// Can not be set simultaneously as lockHeight
	void lockWidth(const float width);
	// Locks the height to the set amount, width is adjusted depending on aspect ratio
	// Can not be set simultaneously as lockWidth
	void lockHeight(const float height);

	// Zooms by the given amount
	void zoom(const float& amount);

	// Returns the view to be applied to the window using sf::RenderWindow.setView(view);
	const sf::View& getView() const;

private:
	// Makes sure that the camera is not larger in any direction than the set constraints
	void checkSize();

private:
	sf::View m_view;
	const sf::RenderWindow& m_window;
	sf::FloatRect m_constraints;
	float m_zoom;
	bool m_hasConstraints;
	sf::Vector2f m_center;

	float m_lockedWidth, m_lockedHeight;

};

