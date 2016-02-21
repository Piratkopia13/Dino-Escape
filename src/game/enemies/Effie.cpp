#include "Effie.h"

Effie::Effie(GameWorld& world, sf::Vector2f bottomCenterPosition)
: Enemy(world)
, m_fireballCooldown(sf::seconds(.9f)) // How often Effie can shoot when he sees the player
{

	health = 2;

	sprite.move(bottomCenterPosition);

	// Possible idle animation, make it slow tho
	m_idleAnimation.setSpriteSheet(*enemiesTexture);
	m_idleAnimation.createFrames(16, 16, 16, 16, 2);

	m_shootAnimation.setSpriteSheet(*enemiesTexture);
	m_shootAnimation.createFrames(16, 16, 0, 16, 3);

	sprite.setAnimation(m_idleAnimation);

	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	sprite.setScale(spriteScale);

	sprite.setFrameTime(sf::seconds(0.3f));

	sprite.move(0, -bounds.height);

}

void Effie::update(const sf::Time& dt) {

	// Update parent
	Entity::update(dt);

	sf::Vector2f myPos = sprite.getPosition();
	sf::Vector2f playerPos = world->getPlayer()->getCenterPos();

	// Raycast
	bool rayIntersects = world->getMap()->isLineColliding(myPos, playerPos);

	if (!rayIntersects) {

		// Check what direction effie is looking
		if (playerPos.x < myPos.x) {
			// Flip
			sprite.setScale(-spriteScale.x, spriteScale.y);
		} else {
			// Flip back
			sprite.setScale(spriteScale.x, spriteScale.y);
		}


		// Apply bullet cooldown
		m_lastFireballTime += dt;
		if (m_lastFireballTime >= m_fireballCooldown) {

			// Fire a bullet towards the player
			float bulletSpeed = 4.0f;
			sf::Vector2f dir = playerPos - myPos;

			sf::Vector2f bulletStart = myPos + Utils::normalize(dir) * 5.0f; // Add an offset from the center
			bulletStart.y += 6.0f; // Shoot from the mouth

			// Apply slight randomization to bullet direction
			dir.x += rand() / ((float)RAND_MAX + 1) * 40 - 20.0f;
			dir.y += rand() / ((float)RAND_MAX + 1) * 40 - 20.0f;

			sf::Vector2f bulletDir = Utils::normalize(dir);

			sf::Vector2f bulletVelocity = bulletSpeed * bulletDir;
			world->getBulletSystem().fireBullet(Bullet::FIREBALL, bulletStart, bulletVelocity, this);

			// Reset cooldown timer
			m_lastFireballTime = sf::Time::Zero;
			
			// Play shoot animation
			sprite.play(m_shootAnimation);
			// Sync animation with bullets
			sprite.setFrame(0, true);
		}


	} else {
		sprite.play(m_idleAnimation);
	}
	sprite.update(dt);

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