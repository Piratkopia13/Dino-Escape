#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position) {

	sprite.move(position);
	
	m_texture.loadFromFile("res/textures/enemies.png");
	walkAnimation.setSpriteSheet(m_texture);

}