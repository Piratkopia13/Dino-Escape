#pragma once

#include <memory>

#include "../Common.h"
#include "Bullet.h"
#include "../TextureManager.h"

class GameWorld;

class Entity : public sf::Drawable {

	public:
		typedef std::unique_ptr<Entity> EntityPtr;

	public:
		Entity() {}

		virtual void update(sf::Time dt) = 0;
		virtual void handleInput(sf::Keyboard::Key key, bool isPressed) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		// Called by BulletSystem when a bullet hits this entity
		virtual void hitByBullet(Bullet* blt) {}

		virtual sf::Transformable& getTransformable() = 0;
		virtual sf::FloatRect getGlobalBounds() = 0;
		virtual sf::Vector2f getCenterPos() const = 0;

		friend class GameWorld;

	public:
		// Pointers to the GameWorld that the entity is part of
		GameWorld* world;

		sf::Vector2f velocity; // Current velocity
		sf::Vector2f lastVelocity; // Velocity last frame, used for interpolation

		bool isGrounded = false; // Set by GameWorld, indicates if the object is standing on ground or is in air
		int health = 1; 
		bool isDead = false; // Flag indicating if GameWorld should remove this entity

		// Interpolation step values. Modifies how "slippery" an entity should be
		sf::Vector2f interpolationStepOnGround = sf::Vector2f(.26f, .1f);
		sf::Vector2f interpolationStepInAir = sf::Vector2f(.09f, .1f);

	private:
		bool isGroundedNextFrame = false;

};