#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "animations\AnimatedSprite.hpp"
#include "Entity.h"

class Player : public Entity {

	public:
		Player();

		virtual void handleInput(sf::Keyboard::Key key, bool isPressed);
		virtual void update(sf::Time dt);

		//void shouldCollideWith(TileMap& map);
		//const sf::Vector2f getCenterPos() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual sf::Transformable& getTransformable();
		virtual sf::FloatRect getGlobalBounds() const;
		virtual sf::Vector2f getCenterPos() const;

		//std::vector<sf::RectangleShape> debug_collisionShapes;
		
		
	private:
		/*sf::Vector2f resolveCollisions(sf::Vector2f& velocity);
		sf::Vector2f getCollisionOverlap(sf::FloatRect& bb);*/

	private:
		AnimatedSprite m_sprite;
		//TileMap* m_collisionMap;

		bool m_isJumping, m_isMovingLeft, m_isMovingRight;
		bool m_wasMovingLeft, m_wasMovingRight;

		sf::Texture m_walkingSheet,
			m_standingSheet,
			m_turnSheet;
		Animation m_walkingAnimation,
			m_standingAnimation,
			m_turnAnimation;

		float m_spriteScale;

};

