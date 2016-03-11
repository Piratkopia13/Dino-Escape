#pragma once

#include "Enemy.h"
#include "../world/GameWorld.h"

// One type of Enemy
// Will walk back and forth
// Damages the player if walked into
// Can be jumped on to squash
class Blobber : public Enemy {

	public:
		Blobber(GameWorld& world, sf::Vector2f bottomCenterPosition = sf::Vector2f(0, 0), bool facingRight = true);

		// Update the Blobber
		virtual void update(const sf::Time& dt);
		// Draw the Blobber
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// Called by the BulletSystem whan a bullet hits this entity
		virtual void hitByBullet(Bullet* blt);
		// Called by the GameWorld when another entity collides with this one
		virtual void collidedWith(Entity* collider);

		// Getters
		virtual sf::Transformable& getTransformable();
		virtual sf::FloatRect getGlobalBounds();
		virtual sf::Vector2f getCenterPos() const;
		
	private:
		// Moves the blobber back and forth on platforms while avoiding falling down
		void runAI();

	private:
		// Animations for walking and getting squashed
		Animation m_walkAnimation,
			m_splatAnimation;

		// The bounding box of the effie
		sf::FloatRect m_boundingBox;

		// Flags for what the Blobber is doing
		bool m_isMovingLeft, m_isMovingRight;
		bool m_isSplatted;
};