#include "BulletSystem.h"

BulletSystem::BulletSystem()
: m_bulletMaxLifetime(sf::seconds(10.0f)) // Bullets will be destroyed after this time
{
}

void BulletSystem::fireBullet(const Bullet::BulletType type, const sf::Vector2f& from, const sf::Vector2f velocity, const Entity* owner) {

	m_bullets.push_back(Bullet(type, from, velocity, owner));

}

void BulletSystem::update(sf::Time dt) {
	
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
	for (auto b = m_bullets.begin(); b != m_bullets.end(); b++)
		target.draw(*b);

}

void BulletSystem::resolveCollisions(TileMap& map, std::vector<Entity*>& entites) {

	// TODO: Create a tree structure and only check for collisions with entities in same cell
	// TODO: Dont delete too many bullets per frame sice vector.erase is slow as f***, mark the bullets to not render and remove a couple every frame
	
	for (auto it = m_bullets.begin(); it != m_bullets.end();) {

		bool deleteCurrent = false;

		// Check collision with entities
		for (auto& entity : entites) {
			if (entity != it->getOwner()) { // Dont check for collisions on bullets owner

				if (entity->getGlobalBounds().intersects(it->getGlobalBounds())) {
					entity->hitByBullet(&(*it)); // Herp derp iterator flerp
					deleteCurrent = true;

					break; // Bullets can only hit ONE entity
				}

			}
		}

		// Check collision with map
		if (map.isPointColliding(it->getPosition()))
			deleteCurrent = true;

		// Delete current bullet if flagged
		if (deleteCurrent)
			it = m_bullets.erase(it);
		else
			++it;
	}

}