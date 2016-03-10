#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "world/Entity.h"
#include "../animations/AnimatedSprite.hpp"
#include "world/GameWorld.h"

#include "../debug/DebugRenderer.h"

// The player entity
// There should only be one of these in the world
class Player : public Entity {

	public:
		// Constructor takes the world as a paramater to be able to use the context
		Player(GameWorld& world);

		// Handles key input to control the player
		virtual void handleInput(sf::Keyboard::Key key, bool isPressed);
		// Updates the player
		virtual void update(const sf::Time& dt);

		// Called by the GameWorld when a bullet just hit the player
		virtual void hitByBullet(Bullet* blt);
		// Called by the GameWorld when another entity just collided with the player
		virtual void collidedWith(Entity* collider) {}

		// Draws the player
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// Getters
		virtual sf::Transformable& getTransformable();
		virtual sf::FloatRect getGlobalBounds();
		virtual sf::Vector2f getCenterPos() const;
		
		
	private:
		// Fires the player's gun if the cooldown timer is inactive
		void fireGun();
		// Turns the player left or right
		void turn(bool left);

	private:
		// The bounding box of the player, slightly smaller than the sprite
		sf::FloatRect m_boundingBox;

		// Flags for what the player is doing
		bool m_isJumping, m_isMovingLeft, m_isMovingRight, m_isShooting;
		bool m_justJumped, m_inJump;
		bool m_isLookingLeft;

		// Animations
		Animation m_walkingAnimation,
			m_standingAnimation,
			m_shootAnimation;

		// Cooldown timer for bullets
		const sf::Time m_bulletCooldown;
		// How long ago the last bullet was fired
		sf::Time m_lastBulletTime;

		// Jump stuff
		const sf::Time m_maxJumpTime;
		sf::Time m_currentJumpTime;

		// Scale of the sprite
		float m_spriteScale;

};

