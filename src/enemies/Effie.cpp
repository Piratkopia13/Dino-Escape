#include "Effie.h"

Effie::Effie(sf::Vector2f position)
	: Enemy(position) {

	// Set up animation
	int width = 16, height = 16;
	int startX = 0, startY = 16;
	/*for (int i = 0; i < 3; i++)
		m_walkAnimation.addFrame(sf::IntRect(startX + i * width, startY, width, height));*/

	// Possible idle animation, make it slow tho
	m_walkAnimation.addFrame(sf::IntRect(0, 16, width, height));
	m_walkAnimation.addFrame(sf::IntRect(32, 16, width, height));

	m_sprite.setFrameTime(sf::seconds(0.3f));

}

#include <iostream>
void Effie::update(sf::Time dt) {

	m_sprite.play(m_walkAnimation);
	m_sprite.update(dt);

	//std::cout << "Vel: " << velocity.x << ", " << velocity.y << " - ";
	//std::cout << lastVelocity.y << std::endl;

	if (isGrounded) {
		velocity.y = -8000.0f * dt.asSeconds();
	}

}

void Effie::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(m_sprite);

}

sf::Transformable& Effie::getTransformable() {
	return m_sprite;
}
sf::FloatRect Effie::getGlobalBounds() const {
	return m_sprite.getGlobalBounds();
}
sf::Vector2f Effie::getCenterPos() const {
	return m_sprite.getPosition();
}