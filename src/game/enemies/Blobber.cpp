#include "Blobber.h"

Blobber::Blobber(GameWorld& world, sf::Vector2f bottomCenterPosition)
: Enemy(world)
, m_isSplatted(false)
{

	// Set initial health
	setHealth(5);

	// Move to the set position
	sprite.move(bottomCenterPosition);


	// Set up animations
	m_walkAnimation.setSpriteSheet(*enemiesTexture);
	m_walkAnimation.createFrames(16, 16, 0, 0, 3);

	m_splatAnimation.setSpriteSheet(*enemiesTexture);
	m_splatAnimation.createFrames(16, 16, 0, 48, 3);

	// Set default animation
	currentAnimation = &m_walkAnimation;
	sprite.setAnimation(m_walkAnimation);

	sprite.setOrigin(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
	spriteScale = sf::Vector2f(1.7f, 1.7f);
	sprite.setScale(spriteScale);

	m_debugPoint.setSize(sf::Vector2f(1.0f, 1.0f));
	m_debugPoint.setFillColor(sf::Color::Red);

	m_isMovingRight = true;


	// Set up properties

	interpolationStepOnGround.x = 0.01f; // Slippery
	interpolationStepInAir.x = 0.003f; // Even more slippery

	hitByBulletXMultiplier = 3.0f; // Raise this since the x interpolation is low


	// Move up by bounds height since original position is defined as the bottom center pos
	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.move(0, -bounds.height);

	// Hardcoded bounding box
	m_boundingBox = bounds;
	m_boundingBox.height -= 5;
}

void Blobber::update(const sf::Time& dt) {

	if (!m_isSplatted) {

		float speed = 17.f * dt.asSeconds();

		if (m_isMovingLeft) {
			velocity.x -= speed;
			sprite.setScale(-spriteScale.x, spriteScale.y);
		} else if (m_isMovingRight) {
			velocity.x += speed;
			sprite.setScale(spriteScale.x, spriteScale.y);
		}

		runAI();

	}

	// Update parent
	Entity::update(dt);

#ifdef ENABLE_DEBUG_SHAPES
	DebugRenderer::addShape(getGlobalBounds(), sf::Color::Blue);
#endif

}

//
// AI explanation:
// Moves back and forth on platforms while avoiding falling down
//
void Blobber::runAI() {

	// No need to check if we are in the air
	if (!isGrounded())
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
	if (!getGameWorld().getMap()->isPointColliding(bottomCheckPoint)) {
		
		// Reverse horizontal movement
		//velocity.x *= -1.f;
		m_isMovingLeft = !m_isMovingLeft;
		m_isMovingRight = !m_isMovingRight;

		// now return since we dont care about side collisions
		return;

	}

	// Check if we need to turn to avoid getting stuck in a wall
	if (getGameWorld().getMap()->isPointColliding(sideCheckPoint)) {

		// Reverse horizontal movement
		//velocity.x *= -1.f;
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

		// Player collided from side or bottom and should take damage
		sf::Vector2f pushBack(collider->getCenterPos() - getCenterPos());
		pushBack = Utils::normalize(pushBack);
		pushBack *= 20.f;
		pushBack.y -= 20.f;

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