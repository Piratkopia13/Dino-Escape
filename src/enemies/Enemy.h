#pragma once

#include <SFML\Graphics.hpp>

#include "..\animations\AnimatedSprite.hpp"
#include "..\world\Entity.h"

class Enemy : public Entity {

	public:
		Enemy(sf::Vector2f position = sf::Vector2f(0,0));

		virtual void handleInput(sf::Keyboard::Key key, bool isPressed) {}; // Enemies dont use key input
		virtual void update(sf::Time dt) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		virtual sf::Transformable& getTransformable() = 0;
		virtual sf::FloatRect getGlobalBounds() const = 0;
		virtual sf::Vector2f getCenterPos() const = 0;


	protected:
		sf::Texture texture;
		AnimatedSprite sprite;
		Animation walkAnimation;
		sf::Vector2f spriteScale = sf::Vector2f(2.0f, 2.0f);


};