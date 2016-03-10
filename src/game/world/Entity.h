#pragma once

#include <memory>

#include "../../animations/AnimatedSprite.hpp"
#include "../../Common.h"
#include "Bullet.h"
#include "../../TextureManager.h"

// Forward declare the GameWorld
class GameWorld;

// The base class of all entities in the game
// Should be added to the GameWorld
class Entity : public sf::Drawable {

	public:
		typedef std::unique_ptr<Entity> EntityPtr;

	public:
		Entity();

		// Update the entity
		virtual void update(const sf::Time& dt);
		// Called when a key is pressed or released
		virtual void handleInput(sf::Keyboard::Key key, bool isPressed) = 0;
		// Draws the entity
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// Called by BulletSystem when a bullet hits this entity
		virtual void hitByBullet(Bullet* blt);
		// Called by GameWorld when another entity collides with this one
		virtual void collidedWith(Entity* collider) = 0;

		// Abstract getters
		virtual sf::Transformable& getTransformable() = 0;
		virtual sf::FloatRect getGlobalBounds() = 0;
		virtual sf::Vector2f getCenterPos() const = 0;

		// Setters
		void setWorld(GameWorld* world);
		void setHealth(const int health);
		void heal(const int value);
		void damage(const int value);
		void damage(const int value, const sf::Vector2f pushBack);
		void destroy();
		void setVelocity(const sf::Vector2f& velocity);
		void stopMoving();

		// Getters
		GameWorld& getGameWorld() const;
		int getHealth() const;
		bool isDead() const;
		bool isGrounded() const;
		const sf::Vector2f& getVelocity() const;
		const sf::Vector2f& Entity::getLastVelocity() const;

		// Give GameWorld access to private variables
		// Such as m_isGrounded and m_lastVelocity
		friend class GameWorld;

	protected:
		
		// The sprite of the entity
		AnimatedSprite sprite;
		// A pointer to the current animation, if there is one
		Animation* currentAnimation;

		// Current velocity
		sf::Vector2f velocity;

		// Interpolation step values
		// Modifies how "slippery" an entity should move
		sf::Vector2f interpolationStepOnGround;
		sf::Vector2f interpolationStepInAir;

		// How heigh the entity should jump when hit by a bullet
		float hitByBulletJumpValue;
		// What the bullets velocity should be multiplied with when added to the entity's velocity
		float hitByBulletXMultiplier;

		// How long the entity should not take damage after just having taken damage
		sf::Time invulnerableTime;

	private:
		// Pointer to the GameWorld that the entity is part of
		GameWorld* m_world;

		// Velocity last frame, used for interpolation
		sf::Vector2f m_lastVelocity;

		// Set by GameWorld, indicates if the object is standing on ground or is in air
		bool m_isGrounded;
		bool m_isGroundedNextFrame;

		// Flag indicating if GameWorld should remove this entity
		bool m_isDead;

		// The health of the entity
		int m_health;

		// Variables for flashing the entity red when hit by a bullet
		sf::Time m_hitFlashTimer;
		const sf::Time m_flashTime;

		sf::Time m_invulnerableTimer;

};