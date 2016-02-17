#pragma once

#include "Enemy.h"
#include "..\world\GameWorld.h"

class Effie : public Enemy {

public:
	Effie(GameWorld& world, sf::Vector2f position = sf::Vector2f(0, 0));

	virtual void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void hitByBullet(Bullet* blt);

	virtual sf::Transformable& getTransformable();
	virtual sf::FloatRect getGlobalBounds();
	virtual sf::Vector2f getCenterPos() const;

private:
	const sf::Texture* m_texture;
	AnimatedSprite m_sprite;
	Animation m_idleAnimation, m_shootAnimation;
	const sf::Time m_fireballCooldown;
	sf::Time m_lastFireballTime;


};