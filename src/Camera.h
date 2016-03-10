#pragma once

#include <SFML\Graphics.hpp>

class Camera {

public:
	Camera(const sf::RenderWindow& window);

	// Updates the camera position and zoom
	void update(sf::Time& dt);

	// Resizes the viewport to the new aspect ratio
	void handleResize(const sf::Event::SizeEvent& size);
	// Interpolates and moves the camera to the specified position
	void moveTo(const sf::Vector2f& position);
	// Sets the cameras center position with no interpolation
	void setPosition(const sf::Vector2f& position);

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
	// Returns the size of the view
	const sf::Vector2f& getSize() const;

private:
	// Makes sure that the camera is not larger in any direction than the set constraints
	void checkSize();
	
private:
	// The acual sfml view instance
	sf::View m_view;
	// Reference to the active render window
	const sf::RenderWindow& m_window;

	// Constraints that limit what the camera can show
	sf::FloatRect m_constraints;
	// Whether or not the camera has constraints
	bool m_hasConstraints;

	// The target zoom value
	float m_zoom;
	// The current zoom value, used to interpolate towards the target zoom value
	float m_currentZoom;
	// The viewport size of the camera
	sf::Vector2f m_size;
	// The center position of the camera
	sf::Vector2f m_center;

	// Whether the size of one dimension is locked or not
	float m_lockedWidth, m_lockedHeight;

};

