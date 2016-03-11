#pragma once

#include <memory>
#include <SFML\Graphics.hpp>

// Forward declare Entity
class Entity;

// Bullets used by the BulletSystem
class Bullet {

	public:
		// Type of the bullet
		enum BulletType {
			NORMAL,
			FIREBALL
		};

		// Befriend the BulletSystem
		friend class BulletSystem;

	public:
		Bullet(const BulletType type, const sf::Vector2f& from, const sf::Vector2f& velocity, const Entity* owner);

		// Update the bullet
		void update(sf::Time dt);

		// Getters
		const sf::Vector2f& getPosition() const;
		const Entity* getOwner() const;
		Bullet::BulletType getType() const;
		float getRotation() const;
		const sf::Vector2f& getVelocity() const;
		const bool hasHit() const;

		// Returns wheather or not the bullet should stay rendering for some time after it has hit
		bool shouldLinger() const;
private:
		// Pointer to who shot the bullet
		const Entity* m_owner;
		// The type
		BulletType m_type;
		// The velocity of the bullet
		sf::Vector2f m_velocity;

		// The angle of rotation for the bullet
		float m_rotation;
		// The current position of the bullet
		sf::Vector2f m_position;
		// How long the bullet has been alive
		sf::Time m_timeAlive;
		// Wheather or not the bullet has hit something
		bool m_hasHit;
		// For how long the bullet has been lingering after having hit something
		sf::Time m_timeDead;
};