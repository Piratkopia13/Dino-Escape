#include "BulletSystem.h"

BulletSystem::BulletSystem()
: m_bulletMaxLifetime(sf::seconds(10.0f)) // Bullets will be destroyed after this time
, m_bulletMaxDeadTime(sf::seconds(.05f))
{

	m_shapeNormal.setFillColor(sf::Color::Yellow);
	m_shapeNormal.setSize(sf::Vector2f(1.5f, 1.5f));

	m_texFireball.loadFromFile("res/textures/items.png");

	m_animFireball.setSpriteSheet(m_texFireball);
	m_animFireball.createFrames(16, 16, 0, 32, 3);

	// TODO: use this animation when bullet hit something
	m_animFireballHit.setSpriteSheet(m_texFireball);
	m_animFireballHit.createFrames(16, 16, 48, 32, 1);

	m_shapeFireball.play(m_animFireball);
	m_shapeFireball.setFrameTime(sf::seconds(.1f));
	m_shapeFireball.setOrigin(m_shapeFireball.getLocalBounds().width / 2.0f, m_shapeFireball.getLocalBounds().height / 2.0f);

}

void BulletSystem::fireBullet(const Bullet::BulletType type, const sf::Vector2f& from, const sf::Vector2f velocity, const Entity* owner) {

	m_bullets.push_back(Bullet(type, from, velocity, owner));

}

void BulletSystem::update(sf::Time dt) {
	
	// Update the animation
	m_shapeFireball.play(m_animFireball);
	m_shapeFireball.update(dt);

	for (auto it = m_bullets.begin(); it != m_bullets.end();) {

		// Update bullet
		it->update(dt);

		// Remove it if it has been alive for too long
		if (it->m_timeAlive >= m_bulletMaxLifetime)
			it = m_bullets.erase(it);
		else
			++it;

	}

}

void BulletSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// Range based loop since the method is const
	for (auto const& b : m_bullets) {

		switch (b.getType()) {
		case Bullet::NORMAL:

			const_cast<sf::RectangleShape&>(m_shapeNormal).setPosition(b.getPosition());
			target.draw(m_shapeNormal);

			break;
		case Bullet::FIREBALL:

			m_shapeFireball.setPosition(b.getPosition());
			m_shapeFireball.setRotation(b.getRotation());
			
			// Change animation if the bullet has hit and is lingering
			if (b.hasHit())
				m_shapeFireball.play(m_animFireballHit);
			else
				m_shapeFireball.play(m_animFireball);

			target.draw(m_shapeFireball);

			break;
		}

	}

}

void BulletSystem::resolveCollisions(TileMap& map, std::vector<Entity::EntityPtr>& entites) {

	// TODO: Create a tree structure and only check for collisions with entities in same cell
	// TODO: Dont delete too many bullets per frame sice vector.erase is slow as f***, mark the bullets to not render and remove a couple every frame
	
	for (auto it = m_bullets.begin(); it != m_bullets.end();) {

		bool advance = false;

		// Remove fireballs that has hit after the MaxDeadTime has expired
		if ((it->shouldLinger() && it->m_timeDead >= m_bulletMaxDeadTime) || (!it->shouldLinger() && it->hasHit())) {
			it = m_bullets.erase(it);
			continue;
		} else
			advance = true;


		bool markCurrentAsHit = false;

		// Check collision with entities
		for (auto& entity : entites) {
			if (entity.get() != it->getOwner()) { // Dont check for collisions on bullets owner

				sf::FloatRect bounds;
				switch (it->getType()) {
				case Bullet::NORMAL:
					m_shapeNormal.setPosition(it->getPosition());
					bounds = m_shapeNormal.getGlobalBounds();
					break;
				case Bullet::FIREBALL:
					m_shapeFireball.setPosition(it->getPosition());
					bounds = m_shapeFireball.getGlobalBounds();
					break;
				}

				if (!it->hasHit() && entity->getGlobalBounds().intersects(bounds)) {
					entity->hitByBullet(&(*it)); // Herp derp iterator flerp
					markCurrentAsHit = true;

					break; // Bullets can only hit ONE entity
				}

			}
		}

		// Check collision with map
		// TODO : check bullet bounds instead of just position
		if (map.isPointColliding(it->getPosition()))
			markCurrentAsHit = true;

		// Delete current bullet if flagged
		if (markCurrentAsHit) {
			it->m_velocity = sf::Vector2f(0.f, 0.f);
			it->m_hasHit = true;
		}

		// Add to the iterating if the current is not deleted already
		if (advance)
			++it;

	}

}