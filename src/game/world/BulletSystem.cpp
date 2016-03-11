#include "BulletSystem.h"

BulletSystem::BulletSystem(Context& context)
: m_bulletMaxLifetime(sf::seconds(10.0f)) // Bullets will be destroyed after this time
, m_bulletMaxDeadTime(sf::seconds(.05f))
, m_context(context)
{

	// Set up the rendering shape for normal bullets
	m_shapeNormal.setFillColor(sf::Color::Yellow);
	m_shapeNormal.setSize(sf::Vector2f(1.5f, 1.5f));
	m_shapeNormal.setTexture(&context.textures->get(Textures::Default));

	// Set up the animation for flying fireballs
	m_animFireball.setSpriteSheet(context.textures->get(Textures::Items));
	m_animFireball.createFrames(16, 16, 0, 32, 3);

	// Set up the animation for fireballs that has hit something
	m_animFireballHit.setSpriteSheet(context.textures->get(Textures::Items));
	m_animFireballHit.createFrames(16, 16, 48, 32, 1);

	// Set the default animation
	m_shapeFireball.play(m_animFireball);
	// Fast updates
	m_shapeFireball.setFrameTime(sf::seconds(.1f));
	// Move the origin to the center for rotations and collision to work better
	m_shapeFireball.setOrigin(m_shapeFireball.getLocalBounds().width / 2.0f, m_shapeFireball.getLocalBounds().height / 2.0f);

}

void BulletSystem::fireBullet(const Bullet::BulletType type, const sf::Vector2f& from, const sf::Vector2f velocity, const Entity* owner) {

	m_bullets.push_back(Bullet(type, from, velocity, owner));

}

void BulletSystem::update(sf::Time dt) {
	
	// Update the animation
	m_shapeFireball.play(m_animFireball);
	m_shapeFireball.update(dt);

	// Loop through all bullets
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

		// Draw depending on what type the bullet is
		switch (b.getType()) {
		case Bullet::NORMAL:

			// Update the position of the shape
			m_shapeNormal.setPosition(b.getPosition());
			// Draw it
			target.draw(m_shapeNormal, states);

			break;
		case Bullet::FIREBALL:

			// Update the position of the shape
			m_shapeFireball.setPosition(b.getPosition());
			// Update the rotation of the shape
			m_shapeFireball.setRotation(b.getRotation());
			
			// Change animation if the bullet has hit and is lingering
			if (b.hasHit())
				m_shapeFireball.play(m_animFireballHit);
			else
				m_shapeFireball.play(m_animFireball);

			// Draw it
			target.draw(m_shapeFireball, states);

			break;
		}

	}

}

void BulletSystem::resolveCollisions(TileMap& map, std::vector<Entity::EntityPtr>& entites) {

	// TODO: Create a tree structure and only check for collisions with entities in same cell
	// TODO: Dont delete too many bullets per frame sice vector.erase is really expensive, mark the bullets to not render and remove a couple every frame.
	//		 Possible other solution is to find a better std list type
	
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
			// Dont check for collisions on bullets owner
			if (entity.get() != it->getOwner()) {

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

		// Check map collision with the center point of the bullet
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