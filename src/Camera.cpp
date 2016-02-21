#include "Camera.h"

Camera::Camera(const sf::RenderWindow& window)
: m_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))
, m_window(window)
, m_constraints(0,0,0,0)
, m_zoom(1.f)
, m_hasConstraints(false)
, m_lockedWidth(0.f)
, m_lockedHeight(0.f)
{
}

void Camera::setConstraints(const sf::FloatRect& constraints) {
	m_constraints = constraints;
	checkSize();
	m_view.zoom(m_zoom);
	m_hasConstraints = true;

	checkSize();
}

void Camera::lockWidth(const float width) {
	m_lockedWidth = width;
	// Set size to width and height depending on aspect ratio
	m_view.setSize(width, width * m_window.getSize().y / m_window.getSize().x);

	checkSize();
}
void Camera::lockHeight(const float height) {
	m_lockedHeight = height;
	// Set size to height and width depending on aspect ratio
	m_view.setSize(height * m_window.getSize().x / m_window.getSize().y, height);

	checkSize();
}

void Camera::checkSize() {

	// Make sure the camera is smaller than the constraints, otherwise change the view size
	const sf::Vector2f& viewSize = m_view.getSize();
	float aspectRatio = viewSize.x / viewSize.y;
	if (viewSize.x > m_constraints.width) {
		// Fix size to map width
		m_view.setSize(m_constraints.width, m_constraints.width * (1.0f / aspectRatio));
	}
	if (viewSize.y > m_constraints.height) {
		// Fix size to map height
		m_view.setSize(m_constraints.height * aspectRatio, m_constraints.height);
	}

}

void Camera::moveTo(const sf::Vector2f& position) {

	const sf::Vector2f& halfViewSize = m_view.getSize() / 2.f;
	sf::Vector2f newPos = position;

	// If constraint is set
	if (m_constraints.width != 0) {

		// Lock position to the constraints
		if (newPos.x - halfViewSize.x < m_constraints.left)
			newPos.x = halfViewSize.x;
		else if (newPos.x + halfViewSize.x > m_constraints.left + m_constraints.width)
			newPos.x = m_constraints.left + m_constraints.width - halfViewSize.x;
		if (newPos.y - halfViewSize.y < m_constraints.top)
			newPos.y = halfViewSize.y;
		else if (newPos.y + halfViewSize.y > m_constraints.top + m_constraints.height)
			newPos.y = m_constraints.top + m_constraints.height - halfViewSize.y;

	}


	// Interpolate
	sf::Vector2f interp = 0.2f * newPos + (1 - 0.2f) * m_view.getCenter();

	// Reset values if they are really low
	if (fabs(interp.x) < 0.0001f) interp.x = 0.f;
	if (fabs(interp.y) < 0.0001f) interp.y = 0.f;

	m_view.setCenter(interp);

}

void Camera::handleResize(const sf::Event::SizeEvent& size) {

	if (m_lockedWidth > 0.f) {
		// Set size to width and height depending on aspect ratio
		m_view.setSize(m_lockedWidth, m_lockedWidth * size.height / size.width);

	} else if (m_lockedHeight > 0.f) {
		// Set size to height and width depending on aspect ratio
		m_view.setSize(m_lockedHeight * m_window.getSize().x / m_window.getSize().y, m_lockedHeight);

	} else {
		// No special with set, just resize to the new window size
		m_view.setSize(size.width, size.height);

	}

	if (m_hasConstraints)
		checkSize();
	m_view.zoom(m_zoom);

}

void Camera::zoom(const float& amount) {
	m_zoom = amount;
	m_view.zoom(m_zoom);
}

const sf::View& Camera::getView() const {
	return m_view;
}