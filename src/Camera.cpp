#include "Camera.h"

Camera::Camera(sf::RenderWindow& window)
: m_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))
, m_window(window)
, m_constraints(0,0,0,0) {

	m_view.zoom(1 / 3.0f);
	updateView();
}

void Camera::setConstraints(sf::FloatRect& constraints) {
	m_constraints = constraints;
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

	m_view.setCenter(interp);

	updateView();

}

void Camera::handleResize(sf::Event::SizeEvent size) {

	//m_view.setViewport(sf::FloatRect(0, 0, size.width, size.height));
	m_view.setSize(size.width, size.height);
	m_view.zoom(1 / 3.0f);
	updateView();

}

void Camera::updateView() {
	m_window.setView(m_view);
}