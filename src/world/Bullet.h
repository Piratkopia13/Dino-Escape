#pragma once

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
	private:
		const Entity* m_owner;
		BulletType m_type;
		sf::Vector2f m_velocity;

		float m_rotation;
		sf::Vector2f m_position;
		sf::Time m_timeAlive;
};