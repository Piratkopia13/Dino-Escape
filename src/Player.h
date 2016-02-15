#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "world\Entity.h"
#include "animations\AnimatedSprite.hpp"
#include "world\GameWorld.h"

#include "debug\DebugRenderer.h"

class Player : public Entity {

	public:
		Player();

		virtual void handleInput(sf::Keyboard::Key key, bool isPressed);
		virtual void update(sf::Time dt);

		virtual void hitByBullet(Bullet* blt);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual sf::Transformable& getTransformable();
		virtual sf::FloatRect getGlobalBounds() const;
		virtual sf::Vector2f getCenterPos() const;

		//std::vector<sf::RectangleShape> debug_collisionShapes;
		
		
	private:
		void fireGun();
		void turn(bool left);

	private:
		AnimatedSprite m_sprite;

		bool m_isJumping, m_isMovingLeft, m_isMovingRight, m_isShooting;
		bool m_justJumped, m_inJump;
		bool m_isLookingLeft;

		sf::Texture m_spriteSheet;
		Animation m_walkingAnimation,
			m_standingAnimation,
			m_shootAnimation;

		const sf::Time m_BulletCooldown;
		sf::Time m_lastBulletTime;

		// Jump stuff
		const sf::Time m_maxJumpTime;
		sf::Time m_currentJumpTime;

		float m_spriteScale;

};

