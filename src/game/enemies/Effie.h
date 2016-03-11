#pragma once

#include "Enemy.h"
#include "..\world\GameWorld.h"

// One type of Enemy
// Will stand still and shoot fireballs at the player
class Effie : public Enemy {

public:
	Effie(GameWorld& world, sf::Vector2f position = sf::Vector2f(0, 0), bool facingRight = true);

	// Update the Effie
	virtual void update(const sf::Time& dt);
	// Draw the Effie
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Called by the BulletSystem whan a bullet hits this entity
	virtual void hitByBullet(Bullet* blt);

	// Getters
	virtual sf::Transformable& getTransformable();
	virtual sf::FloatRect getGlobalBounds();
	virtual sf::Vector2f getCenterPos() const;

private:
	// Animations for standing still and shooting fireballs
	Animation m_idleAnimation, m_shootAnimation;
	// How fast Effies can shoot fireballs
	const sf::Time m_fireballCooldown;
	// How long ago the last shot accure
	sf::Time m_lastFireballTime;


};