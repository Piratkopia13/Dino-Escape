#pragma once

#include <vector>

#include "TileMap.h"
#include "Bullet.h"
#include "../../animations/AnimatedSprite.hpp"
#include "../../PostEffectManager.h"

// A system of bullets
// Handles collisions, rendering etc.
class BulletSystem : sf::Drawable {

	public:
		BulletSystem(Context& context);

		// Fires a new bullet
		void fireBullet(const Bullet::BulletType type, const sf::Vector2f& from, const sf::Vector2f velocity, const Entity* owner);

		// Updates the position of all bullets
		void update(sf::Time dt);
		// Renders all bullets
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// Takes a list of entities to check for collision with
		// Uses the last entity.map to check bullet-map collisions
		// Calls entity.hitByBullet() on collision
		void resolveCollisions(TileMap& map, std::vector<Entity::EntityPtr>& entites);

	private:
		// A list of bullets
		std::vector<Bullet> m_bullets;

		// Reference to the context
		Context& m_context;

		// Lifetime for bullets if they dont collide before it
		const sf::Time m_bulletMaxLifetime;
		// How long the bullet should be visible after it has hit somthing
		const sf::Time m_bulletMaxDeadTime;

		// The shape for normal bullets
		mutable sf::RectangleShape m_shapeNormal;

		// Animations for the fireball bullet
		Animation m_animFireball, m_animFireballHit;
		// The sprite for the fireball bullet
		mutable AnimatedSprite m_shapeFireball;

};
