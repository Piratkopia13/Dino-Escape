#pragma once

#include <vector>

#include "TileMap.h"
#include "Bullet.h"
#include "../../animations/AnimatedSprite.hpp"

class BulletSystem : sf::Drawable {

	public:
		BulletSystem();

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
		std::vector<Bullet> m_bullets;

		// Lifetime for bullets if they dont collide before it
		const sf::Time m_bulletMaxLifetime;
		// How long the bullet should be visible after it has hit somthing
		const sf::Time m_bulletMaxDeadTime;

		mutable sf::RectangleShape m_shapeNormal;

		sf::Texture m_texFireball;
		Animation m_animFireball, m_animFireballHit;
		mutable AnimatedSprite m_shapeFireball;

};
