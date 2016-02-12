#include "Blobber.h"

Blobber::Blobber(sf::Vector2f bottomCenterPosition)
: Enemy(bottomCenterPosition)
{

	// Set up animation
	int width = 16, height = 16;
	int startX = 0, startY = 0;
	for (int i = 0; i < 3; i++)
		walkAnimation.addFrame(sf::IntRect(startX + i * width, startY, width, height));

	sprite.setAnimation(walkAnimation);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
	spriteScale = sf::Vector2f(1.7f, 1.7f);
	sprite.setScale(spriteScale);

	m_debugPoint.setSize(sf::Vector2f(1.0f, 1.0f));
	m_debugPoint.setFillColor(sf::Color::Red);

	m_isMovingRight = true;

	interpolationStepOnGround.x = 0.01f; // Slippery

	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.move(0, -bounds.height);
}

void Blobber::update(sf::Time dt) {

	float speed = 17.f * dt.asSeconds();


	if (m_isMovingLeft) {
		velocity.x = -speed;
		sprite.setScale(-spriteScale.x, spriteScale.y);
	} else if (m_isMovingRight) {
		velocity.x = speed;
		sprite.setScale(spriteScale.x, spriteScale.y);
	}

	sprite.play(walkAnimation);
	sprite.update(dt);
	/*if (isGrounded) {
		velocity.y = -8000.0f * dt.asSeconds();
	}*/

	runAI();

}

//
// AI explanation:
// Moves back and forth on platforms while avoiding falling down
//
void Blobber::runAI() {

	// No need to check if we are in the air
	if (!isGrounded)
		return;
	
	float offset = 1;
	sf::FloatRect bb = sprite.getGlobalBounds();

	sf::Vector2f bottomCheckPoint = sprite.getPosition();
	bottomCheckPoint.y += bb.height / 2.f + offset;

	sf::Vector2f sideCheckPoint = sprite.getPosition();

	if (velocity.x > 0) {
		bottomCheckPoint.x += bb.width / 2.f + offset;
		sideCheckPoint.x += bb.width / 2.f + offset;
	} else if (velocity.x < 0) {
		bottomCheckPoint.x -= bb.width / 2.f + offset;
		sideCheckPoint.x -= bb.width / 2.f + offset;
	}

	// Store point for debug rendering
	m_debugPoint.setPosition(sideCheckPoint);

	// Check if we need to turn to avoid falling
	if (!world->getMap()->isPointColliding(bottomCheckPoint)) {
		
		// Reverse horizontal movement
		velocity.x *= -1.f;
		m_isMovingLeft = !m_isMovingLeft;
		m_isMovingRight = !m_isMovingRight;

		// now return since we dont care about side collisions
		return;

	}

	// Check if we need to turn to avoid getting stuck in a wall
	if (world->getMap()->isPointColliding(sideCheckPoint)) {

		// Reverse horizontal movement
		velocity.x *= -1.f;
		m_isMovingLeft = !m_isMovingLeft;
		m_isMovingRight = !m_isMovingRight;

	}


}

void Blobber::hitByBullet(Bullet* blt) {
	// TODO : make different bullet-types do different amount of damage
	health -= 1;

	if (health <= 0)
		isDead = true; // Tell GameWorld to remove this entity
}

void Blobber::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(sprite);
	//target.draw(m_debugPoint);

}

sf::Transformable& Blobber::getTransformable() {
	return sprite;
}
sf::FloatRect Blobber::getGlobalBounds() const {
	return sprite.getGlobalBounds();
}
sf::Vector2f Blobber::getCenterPos() const {
	return sprite.getPosition();
}