#pragma once

#include <memory>
#include <SFML\Graphics.hpp>

class Entity;

class Bullet {

	public:
		enum BulletType {
			NORMAL,
			FIREBALL
		};

		friend class BulletSystem;

	public:
		Bullet(const BulletType type, const sf::Vector2f& from, const sf::Vector2f& velocity, const Entity* owner);
		~Bullet();

		void update(sf::Time dt);

		// Getters
		const sf::Vector2f& getPosition() const;
		const Entity* getOwner() const;
		Bullet::BulletType getType() const;
		float getRotation() const;
		const sf::Vector2f& getVelocity() const;
		const bool hasHit() const;

		// Returns wheather or not the bullet should stay for some time after it has hit
		bool shouldLinger() const;
private:
		const Entity* m_owner;
		BulletType m_type;
		sf::Vector2f m_velocity;

		float m_rotation;
		sf::Vector2f m_position;
		sf::Time m_timeAlive;
		bool m_hasHit;
		sf::Time m_timeDead;
};