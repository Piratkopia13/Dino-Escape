#pragma once

#include "Enemy.h"
#include "../world/GameWorld.h"

class Effie : public Enemy {

public:
	Effie(sf::Vector2f position = sf::Vector2f(0, 0));

	virtual void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void hitByBullet(Bullet* blt);

	virtual sf::Transformable& getTransformable();
	virtual sf::FloatRect getGlobalBounds() const;
	virtual sf::Vector2f getCenterPos() const;

private:
	Animation m_shootAnimation;
	const sf::Time m_fireballCooldown;
	sf::Time m_lastFireballTime;


};