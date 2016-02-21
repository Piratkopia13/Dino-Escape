#pragma once

#include <memory>

#include "../../animations/AnimatedSprite.hpp"
#include "../../Common.h"
#include "Bullet.h"
#include "../../TextureManager.h"

class GameWorld;

class Entity : public sf::Drawable {

	public:
		typedef std::unique_ptr<Entity> EntityPtr;

	public:
		Entity() : m_flashTime(sf::seconds(.2f)) {}

		virtual void update(const sf::Time& dt) {

			// Update flash timer
			m_hitFlashTimer += dt;
			// Set color to normal if timer has expired
			if (m_hitFlashTimer >= m_flashTime)
				sprite.setColor(sf::Color(255, 255, 255, 255));

		};
		virtual void handleInput(const sf::Keyboard::Key& key, const bool isPressed) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			// Draw the sprite
			target.draw(sprite);
		}

		// Called by BulletSystem when a bullet hits this entity
		virtual void hitByBullet(Bullet* blt) {

			m_hitFlashTimer = sf::Time::Zero;
			// Change color
			sprite.setColor(sf::Color(255, 150, 150, 255));
			// Push the entitiy back
			velocity += blt->getVelocity() * hitByBulletXMultiplier;
			velocity.y -= hitByBulletJumpValue;


			// TODO : make different bullet-types do different amount of damage
			health -= 1;

			if (health <= 0)
				isDead = true; // Tell GameWorld to remove this entity

		}

		virtual sf::Transformable& getTransformable() = 0;
		virtual sf::FloatRect getGlobalBounds() = 0;
		virtual sf::Vector2f getCenterPos() const = 0;

		friend class GameWorld;

	public:
		// Pointers to the GameWorld that the entity is part of
		GameWorld* world;

		AnimatedSprite sprite;

		sf::Vector2f velocity; // Current velocity
		sf::Vector2f lastVelocity; // Velocity last frame, used for interpolation

		bool isGrounded = false; // Set by GameWorld, indicates if the object is standing on ground or is in air
		int health = 1;
		bool isDead = false; // Flag indicating if GameWorld should remove this entity

		// Interpolation step values. Modifies how "slippery" an entity should be
		sf::Vector2f interpolationStepOnGround = sf::Vector2f(.26f, .1f);
		sf::Vector2f interpolationStepInAir = sf::Vector2f(.09f, .1f);

		// How heigh the entity should jump when hit by a bullet
		float hitByBulletJumpValue = 40.f;
		// What the bullets velocity should be multiplied with when added to the entity velocity
		float hitByBulletXMultiplier = 1.f;

	private:
		bool isGroundedNextFrame = false;

		// Variables for flashing the entity red when hit by a bullet
		sf::Time m_hitFlashTimer;
		const sf::Time m_flashTime;

};