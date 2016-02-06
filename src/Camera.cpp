#include "Camera.h"

Camera::Camera(sf::RenderWindow& window)
: m_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))
, m_window(window) {

	m_view.zoom(1 / 3.0f);
	updateView();
}

void Camera::update(sf::Time dt) {

}

void Camera::moveTo(const sf::Vector2f& position) {

	m_view.setCenter(position);
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