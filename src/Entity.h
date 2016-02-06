#pragma once

#include <SFML\Graphics.hpp>

class TileMap;

class Entity : public sf::Drawable {

	public:
		Entity() {}

		virtual void update(sf::Time dt) = 0;
		virtual void handleInput(sf::Keyboard::Key key, bool isPressed) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		virtual sf::Transformable& getTransformable() = 0;
		virtual sf::FloatRect getGlobalBounds() const = 0;
		virtual sf::Vector2f getCenterPos() const = 0;

	public:
		TileMap* map;
		Entity* player;
		sf::Vector2f velocity;
		sf::Vector2f lastVelocity;
		bool isGrounded = false;

		sf::Vector2f interpolationStepOnGround = sf::Vector2f(.26f, .1f);
		sf::Vector2f interpolationStepInAir = sf::Vector2f(.05f, .1f);
};