#pragma once

#include <SFML\Graphics.hpp>

#include "../world/Entity.h"
#include "../../animations/AnimatedSprite.hpp"

// The base class for all enemy entities
class Enemy : public Entity {

	public:
		Enemy(GameWorld& world);

		// Ignore inputs as enemies dont use them
		virtual void handleInput(sf::Keyboard::Key key, bool isPressed) {};
		// Updates the entity
		virtual void update(const sf::Time& dt) = 0;
		// Draws the entitiy
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		
		// Called by the BulletSystem when a bullet hits this entity
		virtual void hitByBullet(Bullet* blt) = 0;
		// Called by the GameWorld when another entity collides with this one
		// Not required to implement by enemies
		virtual void collidedWith(Entity* collider) {};

		// Getters
		virtual sf::Transformable& getTransformable() = 0;
		virtual sf::FloatRect getGlobalBounds() = 0;
		virtual sf::Vector2f getCenterPos() const = 0;


	protected:
		// The common scale factor, can be modified independently
		sf::Vector2f spriteScale;
		// The texture/spritesheet that all enemies share
		const sf::Texture* enemiesTexture;


};