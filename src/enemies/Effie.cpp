#include "Effie.h"

Effie::Effie(GameWorld& world, sf::Vector2f bottomCenterPosition)
: Enemy(world)
, m_fireballCooldown(sf::seconds(.9f)) // How often Effie can shoot when he sees the player
{

	m_sprite.move(bottomCenterPosition);

	m_texture = &world.getTextureManager().get(TextureHolder::ENEMIES);

	// Possible idle animation, make it slow tho
	m_idleAnimation.setSpriteSheet(*m_texture);
	m_idleAnimation.createFrames(16, 16, 16, 16, 2);

	m_shootAnimation.setSpriteSheet(*m_texture);
	m_shootAnimation.createFrames(16, 16, 0, 16, 3);

	m_sprite.setAnimation(m_idleAnimation);

	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	m_sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	m_sprite.setScale(spriteScale);

	m_sprite.setFrameTime(sf::seconds(0.3f));

	m_sprite.move(0, -bounds.height);

}

void Effie::update(sf::Time dt) {

	sf::Vector2f myPos = m_sprite.getPosition();
	sf::Vector2f playerPos = world->getPlayer()->getCenterPos();

	// Raycast
	bool rayIntersects = world->getMap()->isLineColliding(myPos, playerPos);

	if (!rayIntersects) {

		// Check what direction effie is looking
		if (playerPos.x < myPos.x) {
			// Flip
			m_sprite.setScale(-spriteScale.x, spriteScale.y);
		} else {
			// Flip back
			m_sprite.setScale(spriteScale.x, spriteScale.y);
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
			m_sprite.play(m_shootAnimation);
			// Sync animation with bullets
			m_sprite.setFrame(0, true);
		}


	} else {
		m_sprite.play(m_idleAnimation);
	}
	m_sprite.update(dt);

}

void Effie::hitByBullet(Bullet* blt) {
	// TODO : make different bullet-types do different amount of damage
	health -= 1;

	if (health <= 0)
		isDead = true; // Tell GameWorld to remove this entity
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