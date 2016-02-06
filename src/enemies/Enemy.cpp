#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position) {

	m_sprite.move(position);
	m_sprite.scale(2.0f, 2.0f);

	m_texture.loadFromFile("res/textures/enemies.png");
	m_walkAnimation.setSpriteSheet(m_texture);

}