#pragma once

#include "Enemy.h"
#include "../world/GameWorld.h"

class Blobber : public Enemy {

	public:
		Blobber(GameWorld& world, sf::Vector2f bottomCenterPosition = sf::Vector2f(0, 0), bool facingRight = true);

		virtual void update(const sf::Time& dt);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual void hitByBullet(Bullet* blt);
		virtual void collidedWith(Entity* collider);

		virtual sf::Transformable& getTransformable();
		virtual sf::FloatRect getGlobalBounds();
		virtual sf::Vector2f getCenterPos() const;
		
		void runAI();

	private:
		Animation m_walkAnimation,
			m_splatAnimation;

		sf::FloatRect m_boundingBox;

		sf::RectangleShape m_debugPoint;

		bool m_isMovingLeft, m_isMovingRight;
		bool m_isSplatted;
};