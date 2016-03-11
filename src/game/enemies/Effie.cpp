#include "Effie.h"

Effie::Effie(GameWorld& world, sf::Vector2f bottomCenterPosition, bool facingRight)
: Enemy(world)
, m_fireballCooldown(sf::seconds(.9f)) // How often Effie can shoot when he sees the player
{
	// Inital health
	setHealth(2);

	// Set up idle animation
	m_idleAnimation.setSpriteSheet(*enemiesTexture);
	m_idleAnimation.createFrames(16, 16, 16, 16, 2);

	// Set up shoot animation
	m_shootAnimation.setSpriteSheet(*enemiesTexture);
	m_shootAnimation.createFrames(16, 16, 0, 16, 3);

	// Set default animation
	currentAnimation = &m_idleAnimation;
	sprite.setAnimation(*currentAnimation);

	sf::FloatRect bounds = sprite.getGlobalBounds();
	// Move the origin to the center of the sprite
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

	// Set facing direction and scale
	if (!facingRight)
		sprite.setScale(-spriteScale.x, spriteScale.y);
	else
		sprite.setScale(spriteScale);

	// Set animation frame time
	sprite.setFrameTime(sf::seconds(0.3f));

	// Move into position
	sprite.move(bottomCenterPosition);
	sprite.move(0, -bounds.height);

}

void Effie::update(const sf::Time& dt) {

	// Store the current position of the effie
	const sf::Vector2f& myPos = sprite.getPosition();
	// Store a pointer to the player
	Entity* player = getGameWorld().getPlayer();
	// Store the position of the player
	sf::Vector2f playerPos = player->getCenterPos();

	// Raycast from the effies position to the player position and see if it intersects with any map tile
	bool rayIntersects = player->isDead() || getGameWorld().getMap().isLineColliding(myPos, playerPos);

	// Check if the effie can see the player/ray is not intersecting
	if (!rayIntersects) {

		// Check what direction effie is looking
		if (playerPos.x < myPos.x) {
			// Flip
			sprite.setScale(-spriteScale.x, spriteScale.y);
		} else {
			// Flip back
			sprite.setScale(spriteScale);
		}


		// Apply bullet cooldown
		m_lastFireballTime += dt;
		if (m_lastFireballTime >= m_fireballCooldown) {

			// Play fireball shoot sound from the location of the entity
			getGameWorld().getContext().sounds->play(Sounds::ShootFireball, getCenterPos());

			// Fire a bullet towards the player
			float bulletSpeed = 4.0f;
			sf::Vector2f dir = playerPos - myPos;

			// Set the starting position for the bullet. Add an offset from the center
			sf::Vector2f bulletStart = myPos + Utils::normalize(dir) * 5.0f;
			bulletStart.y += 6.0f; // Shoot from the mouth

			// Apply slight randomization to bullet direction
			dir.x += Utils::random(-20.f, 20.f);
			dir.y += Utils::random(-20.f, 20.f);

			// Normalize the value to make all bullets go the same speed
			sf::Vector2f bulletDir = Utils::normalize(dir);

			// Set the bullet velocity
			sf::Vector2f bulletVelocity = bulletSpeed * bulletDir;
			// Fire the bullet
			getGameWorld().getBulletSystem().fireBullet(Bullet::FIREBALL, bulletStart, bulletVelocity, this);

			// Reset cooldown timer
			m_lastFireballTime = sf::Time::Zero;
			
			// Play shoot animation
			currentAnimation = &m_shootAnimation;
			// Sync animation with bullets
			sprite.setFrame(0, true);
		}


	} else {
		// The effie does not see the player, play the idle animation
		currentAnimation = &m_idleAnimation;
	}
	
	// Update parent
	Entity::update(dt);

}

void Effie::hitByBullet(Bullet* blt) {

	// Call parent
	Entity::hitByBullet(blt);

}

void Effie::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// Draw sprite from parent
	Entity::draw(target, states);

}

sf::Transformable& Effie::getTransformable() {
	return sprite;
}
sf::FloatRect Effie::getGlobalBounds() {
	return sprite.getGlobalBounds();
}
sf::Vector2f Effie::getCenterPos() const {
	return sprite.getPosition();
}