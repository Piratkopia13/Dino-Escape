#include "Blobber.h"

Blobber::Blobber(GameWorld& world, sf::Vector2f bottomCenterPosition, bool facingRight)
: Enemy(world)
, m_isSplatted(false)
{

	// Set initial health
	setHealth(5);

	// Set up walk animation
	m_walkAnimation.setSpriteSheet(*enemiesTexture);
	m_walkAnimation.createFrames(16, 16, 0, 0, 3);

	// Set up splat animation
	m_splatAnimation.setSpriteSheet(*enemiesTexture);
	m_splatAnimation.createFrames(16, 16, 0, 48, 3);

	// Set default animation
	currentAnimation = &m_walkAnimation;
	sprite.setAnimation(m_walkAnimation);

	// Move the origin to the center of the sprite
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
	// Set scale
	spriteScale = sf::Vector2f(1.7f, 1.7f);
	sprite.setScale(spriteScale);

	// Set facing direction
	if (!facingRight) {
		m_isMovingLeft = true;
		m_isMovingRight = false;
	} else {
		m_isMovingRight = true;
		m_isMovingLeft = false;
	}

	// Set up entity properties
	interpolationStepOnGround.x = 0.01f; // Slippery
	interpolationStepInAir.x = 0.003f; // Even more slippery
	hitByBulletXMultiplier = 3.0f; // Raise this since the x interpolation is low

	// Move to the set position
	sprite.move(bottomCenterPosition);
	// Move up by bounds height since original position is defined as the bottom center pos
	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.move(0, -bounds.height);

	// Hardcoded bounding box size
	m_boundingBox = bounds;
	m_boundingBox.height -= 5;
}

void Blobber::update(const sf::Time& dt) {

	// Only update things if the Blobber is not splatted
	if (!m_isSplatted) {

		// The movementspeed of the Blobber
		float speed = 17.f * dt.asSeconds();

		// Update velocity and scale depending on which way its facing
		if (m_isMovingLeft) {
			velocity.x -= speed;
			sprite.setScale(-spriteScale.x, spriteScale.y);
		} else if (m_isMovingRight) {
			velocity.x += speed;
			sprite.setScale(spriteScale.x, spriteScale.y);
		}

		// Run the AI
		runAI();

	}

	// Update parent
	Entity::update(dt);

	ADD_DEBUG_SHAPE_IF_ENABLED(getGlobalBounds(), sf::Color::Blue);

}

void Blobber::runAI() {

	// No need to run AI if Blobber is in the air
	if (!isGrounded())
		return;
	
	// The offset from the corner of the Blobber where collision will be checked
	float offset = 1;
	// Sotre the bounds
	sf::FloatRect bb = sprite.getGlobalBounds();

	// A point at the bottom of the Blobber that determines if it needs to turn to avoid falling
	sf::Vector2f bottomCheckPoint = sprite.getPosition();
	bottomCheckPoint.y += bb.height / 2.f + offset;

	// A point to the side of the Blobber that determines if it needs to turn to avoid looking stupid/getting stuck at a wall
	sf::Vector2f sideCheckPoint = sprite.getPosition();

	// Move the points depending on what direction the Blobber is moving
	if (velocity.x > 0) {
		bottomCheckPoint.x += bb.width / 2.f + offset;
		sideCheckPoint.x += bb.width / 2.f + offset;
	} else if (velocity.x < 0) {
		bottomCheckPoint.x -= bb.width / 2.f + offset;
		sideCheckPoint.x -= bb.width / 2.f + offset;
	}

	// Check if we need to turn to avoid falling
	if (!getGameWorld().getMap().isPointColliding(bottomCheckPoint)) {
		
		// Reverse horizontal movement
		m_isMovingLeft = !m_isMovingLeft;
		m_isMovingRight = !m_isMovingRight;

		// Return since we now don't care about side collisions
		return;

	}

	// Check if we need to turn to avoid getting stuck in a wall
	if (getGameWorld().getMap().isPointColliding(sideCheckPoint)) {

		// Reverse horizontal movement
		m_isMovingLeft = !m_isMovingLeft;
		m_isMovingRight = !m_isMovingRight;

	}


}

void Blobber::hitByBullet(Bullet* blt) {

	// Call parent
	Entity::hitByBullet(blt);

}

void Blobber::collidedWith(Entity* collider) {

	// Only care about collision with the player
	if (!dynamic_cast<Player*>(collider))
		return;

	// We dont care if the splat has already occured
	if (m_isSplatted)
		return;

	sf::FloatRect playerBounds = collider->getGlobalBounds();
	// Get the position of the player's bottom on the last frame
	float lastPlayerPosY = playerBounds.top + playerBounds.height - collider->getLastVelocity().y;

	// Check if player jumped on Blobber
	if (lastPlayerPosY <= getGlobalBounds().top) {

		// SPLAT
		m_isSplatted = true;
		m_boundingBox.height -= 15.f; // Make bounds smaller

		// Play splat animation
		currentAnimation = &m_splatAnimation;
		sprite.setFrameTime(sf::seconds(0.04f));
		sprite.setLooped(false);

	} else if (!m_isSplatted) {
		// Player collided from side or bottom
		// Calculate a vector that the player should get pushed back by
		sf::Vector2f pushBack(collider->getCenterPos() - getCenterPos());
		pushBack = Utils::normalize(pushBack);
		pushBack *= 20.f;
		pushBack.y -= 20.f;

		// Damage and push back the player
		collider->damage(1, pushBack);
	}

}

void Blobber::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// Draw sprite from parent
	Entity::draw(target, states);

}

sf::Transformable& Blobber::getTransformable() {
	return sprite;
}
sf::FloatRect Blobber::getGlobalBounds() {
	
	sf::FloatRect globalBounds = sprite.getGlobalBounds();
	
	if (m_isSplatted)
		// Small bounding box when splatted
		m_boundingBox.top = globalBounds.top + 20;
	else
		m_boundingBox.top = globalBounds.top + 5;

	m_boundingBox.left = globalBounds.left;

	return m_boundingBox;

}
sf::Vector2f Blobber::getCenterPos() const {
	return sprite.getPosition();
}