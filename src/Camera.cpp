#include "Camera.h"

Camera::Camera(sf::RenderWindow& window)
: m_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))
, m_window(window)
, m_constraints(0,0,0,0)
, m_zoom(1.f)
, m_hasConstraints(false)
{
	updateView();
}

void Camera::setConstraints(sf::FloatRect& constraints) {
	m_constraints = constraints;
	checkSize();
	m_view.zoom(m_zoom);
	m_hasConstraints = true;
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

	updateView();

}

void Camera::handleResize(sf::Event::SizeEvent size) {

	m_view.setSize(size.width, size.height);
	if (m_hasConstraints)
		checkSize();
	m_view.zoom(m_zoom);
	updateView();

}

void Camera::zoom(float zoom) {
	m_zoom = zoom;
	m_view.zoom(m_zoom);
}

void Camera::updateView() {
	m_window.setView(m_view);
}

const sf::View& Camera::getView() const {
	return m_view;
}