#include "Blobber.h"

Blobber::Blobber(sf::Vector2f position)
: Enemy(position)
{

	// Set up animation
	int width = 16, height = 16;
	int startX = 0, startY = 0;
	for (int i = 0; i < 3; i++)
		m_walkAnimation.addFrame(sf::IntRect(startX + i * width, startY, width, height));

	m_sprite.setFrameTime(sf::seconds(0.15f));

	m_debugPoint.setSize(sf::Vector2f(1.0f, 1.0f));
	m_debugPoint.setFillColor(sf::Color::Red);

}

void Blobber::update(sf::Time dt) {

	m_sprite.play(m_walkAnimation);
	m_sprite.update(dt);

	velocity.x = 10.f * dt.asSeconds();
	/*if (isGrounded) {
		velocity.y = -8000.0f * dt.asSeconds();
	}*/

	runAI();

}

void Blobber::runAI() {
	
	float offset = 5;
	sf::FloatRect bb = m_sprite.getGlobalBounds();
	sf::Vector2f checkPoint = m_sprite.getPosition();
	checkPoint.x -= offset;
	checkPoint.y += bb.height + offset;

	if (velocity.x > 0) {
		checkPoint.x += bb.width + offset * 2;
	}

	// Store point for debug rendering
	m_debugPoint.setPosition(checkPoint);

	bool checkPointColliding = map->isPointColliding(checkPoint);

	if (checkPointColliding) {
		// Reverse x velocity
		velocity.x *= -1.f;
	}


}


void Blobber::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(m_sprite);
	target.draw(m_debugPoint);

}

sf::Transformable& Blobber::getTransformable() {
	return m_sprite;
}
sf::FloatRect Blobber::getGlobalBounds() const {
	return m_sprite.getGlobalBounds();
}
sf::Vector2f Blobber::getCenterPos() const {
	return m_sprite.getPosition();
}