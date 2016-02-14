#include "Blobber.h"

Blobber::Blobber(GameWorld& world, sf::Vector2f bottomCenterPosition)
: Enemy(world)
{

	m_sprite.move(bottomCenterPosition);

	m_texture = &world.getTextureManager().get(TextureHolder::ENEMIES);
	m_walkAnimation.setSpriteSheet(*m_texture);

	// Set up animation
	m_walkAnimation.createFrames(16, 16, 0, 0, 3);

	m_sprite.setAnimation(m_walkAnimation);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f);
	spriteScale = sf::Vector2f(1.7f, 1.7f);
	m_sprite.setScale(spriteScale);

	m_debugPoint.setSize(sf::Vector2f(1.0f, 1.0f));
	m_debugPoint.setFillColor(sf::Color::Red);

	m_isMovingRight = true;

	interpolationStepOnGround.x = 0.01f; // Slippery

	// Move up by bounds height since original position is defined as the bottom center pos
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	m_sprite.move(0, -bounds.height);
}

void Blobber::update(sf::Time dt) {

	float speed = 17.f * dt.asSeconds();


	if (m_isMovingLeft) {
		velocity.x = -speed;
		m_sprite.setScale(-spriteScale.x, spriteScale.y);
	} else if (m_isMovingRight) {
		velocity.x = speed;
		m_sprite.setScale(spriteScale.x, spriteScale.y);
	}

	m_sprite.play(m_walkAnimation);
	m_sprite.update(dt);
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
	sf::FloatRect bb = m_sprite.getGlobalBounds();

	sf::Vector2f bottomCheckPoint = m_sprite.getPosition();
	bottomCheckPoint.y += bb.height / 2.f + offset;

	sf::Vector2f sideCheckPoint = m_sprite.getPosition();

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

	target.draw(m_sprite);
	//target.draw(m_debugPoint);

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