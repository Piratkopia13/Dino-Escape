#include "Effie.h"

Effie::Effie(GameWorld& world, sf::Vector2f bottomCenterPosition, bool facingRight)
: Enemy(world)
, m_fireballCooldown(sf::seconds(.9f)) // How often Effie can shoot when he sees the player
{
	// Inital health
	setHealth(2);

	// Possible idle animation, make it slow tho
	m_idleAnimation.setSpriteSheet(*enemiesTexture);
	m_idleAnimation.createFrames(16, 16, 16, 16, 2);

	m_shootAnimation.setSpriteSheet(*enemiesTexture);
	m_shootAnimation.createFrames(16, 16, 0, 16, 3);

	// Set default animation
	currentAnimation = &m_idleAnimation;
	sprite.setAnimation(*currentAnimation);

	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

	// Set facing direction
	if (!facingRight)
		sprite.setScale(-spriteScale.x, spriteScale.y);
	else
		sprite.setScale(spriteScale);

	sprite.setFrameTime(sf::seconds(0.3f));

	// Move to the set position
	sprite.move(bottomCenterPosition);
	sprite.move(0, -bounds.height);

}

void Effie::update(const sf::Time& dt) {

	sf::Vector2f myPos = sprite.getPosition();
	Entity* player = getGameWorld().getPlayer();
	sf::Vector2f playerPos = player->getCenterPos();

	// Raycast
	bool rayIntersects = player->isDead() || getGameWorld().getMap()->isLineColliding(myPos, playerPos);

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

			sf::Vector2f bulletStart = myPos + Utils::normalize(dir) * 5.0f; // Add an offset from the center
			bulletStart.y += 6.0f; // Shoot from the mouth

			// Apply slight randomization to bullet direction
			dir.x += Utils::random(-20.f, 20.f);
			dir.y += Utils::random(-20.f, 20.f);

			sf::Vector2f bulletDir = Utils::normalize(dir);

			sf::Vector2f bulletVelocity = bulletSpeed * bulletDir;
			getGameWorld().getBulletSystem().fireBullet(Bullet::FIREBALL, bulletStart, bulletVelocity, this);

			// Reset cooldown timer
			m_lastFireballTime = sf::Time::Zero;
			
			// Play shoot animation
			currentAnimation = &m_shootAnimation;
			// Sync animation with bullets
			sprite.setFrame(0, true);
		}


	} else {
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