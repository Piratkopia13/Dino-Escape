#pragma once

#include <SFML\Graphics.hpp>

#include "..\world\Entity.h"
#include "../../animations/AnimatedSprite.hpp"

class Enemy : public Entity {

	public:
		Enemy(GameWorld& world);

		virtual void handleInput(sf::Keyboard::Key key, bool isPressed) {}; // Enemies dont use key input
		virtual void update(const sf::Time& dt) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		virtual void hitByBullet(Bullet* blt) = 0;

		virtual sf::Transformable& getTransformable() = 0;
		virtual sf::FloatRect getGlobalBounds() = 0;
		virtual sf::Vector2f getCenterPos() const = 0;


	protected:
		sf::Vector2f spriteScale = sf::Vector2f(2.0f, 2.0f);
		const sf::Texture* enemiesTexture;


};