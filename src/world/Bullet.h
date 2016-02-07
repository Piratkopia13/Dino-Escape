#pragma once

#include <SFML\Graphics.hpp>

class Entity;

class Bullet : public sf::Drawable {

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
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// Getters
		const sf::Vector2f& getPosition() const;
		const Entity* getOwner() const;
		Bullet::BulletType getType() const;
		sf::FloatRect getGlobalBounds();

	private:
		const Entity* m_owner;
		BulletType m_type;
		sf::Vector2f m_velocity;

		sf::RectangleShape m_shape;
		sf::Time m_timeAlive;
};