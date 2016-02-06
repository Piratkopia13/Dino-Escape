#include "Effie.h"

Effie::Effie(sf::Vector2f position)
	: Enemy(position) {

	// Set up animation
	int width = 16, height = 16;
	int startX = 0, startY = 16;
	/*for (int i = 0; i < 3; i++)
		m_walkAnimation.addFrame(sf::IntRect(startX + i * width, startY, width, height));*/

	// Possible idle animation, make it slow tho
	walkAnimation.addFrame(sf::IntRect(0, 16, width, height));
	walkAnimation.addFrame(sf::IntRect(32, 16, width, height));

	sprite.setFrameTime(sf::seconds(0.3f));

}

#include <iostream>
void Effie::update(sf::Time dt) {

	sprite.play(walkAnimation);
	sprite.update(dt);

	//std::cout << "Vel: " << velocity.x << ", " << velocity.y << " - ";
	//std::cout << lastVelocity.y << std::endl;

	if (isGrounded) {
		velocity.y = -8000.0f * dt.asSeconds();
	}

}

void Effie::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(sprite);

}

sf::Transformable& Effie::getTransformable() {
	return sprite;
}
sf::FloatRect Effie::getGlobalBounds() const {
	return sprite.getGlobalBounds();
}
sf::Vector2f Effie::getCenterPos() const {
	return sprite.getPosition();
}