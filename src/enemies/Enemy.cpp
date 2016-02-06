#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position) {

	sprite.move(position);
	
	texture.loadFromFile("res/textures/enemies.png");
	walkAnimation.setSpriteSheet(texture);

}