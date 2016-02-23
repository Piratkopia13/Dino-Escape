#include "Entity.h"
#include "../Player.h"
#include "../world/GameWorld.h"

Entity::Entity()
: m_flashTime(sf::seconds(.2f))

// Set up default values
, interpolationStepOnGround(sf::Vector2f(.26f, .1f))
, interpolationStepInAir(sf::Vector2f(.09f, .1f))
, hitByBulletJumpValue(88.f)
, hitByBulletXMultiplier(1.f)
, m_isGrounded(false)
, m_isGroundedNextFrame(false)
, m_isDead(false)
, m_health(1)
{

}

void Entity::update(const sf::Time& dt) {

	// Update flash timer
	m_hitFlashTimer += dt;
	// Set color to normal if timer has expired
	if (m_hitFlashTimer >= m_flashTime)
		sprite.setColor(sf::Color(255, 255, 255, 255));

};

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// Draw the sprite
	target.draw(sprite);
}

void Entity::hitByBullet(Bullet* blt) {

	// Play hit sound
	if (dynamic_cast<Player*>(this))
		m_world->getContext().sounds->play(Sounds::HitPlayer, getCenterPos());
	else
		m_world->getContext().sounds->play(Sounds::HitEnemy, getCenterPos());

	m_hitFlashTimer = sf::Time::Zero;
	// Change color
	sprite.setColor(sf::Color(255, 150, 150, 255));
	// Push the entitiy back
	velocity += blt->getVelocity() * hitByBulletXMultiplier;

	velocity.y -= hitByBulletJumpValue;


	// TODO : make different bullet-types do different amount of damage
	m_health -= 1;

	if (m_health <= 0)
		m_isDead = true; // Tell GameWorld to remove this entity

}

void Entity::setWorld(GameWorld* world) {
	m_world = world;
}
void Entity::setHealth(const int health) {
	m_health = health;
}
void Entity::heal(const int value) {
	m_health += value;
}
void Entity::damage(const int value) {
	m_health -= value;
}

GameWorld& Entity::getGameWorld() const {
	return *m_world;
}
int Entity::getHealth() const {
	return m_health;
}
bool Entity::isGrounded() const {
	return m_isGrounded;
}
const sf::Vector2f& Entity::getVelocity() const {
	return velocity;
}
const sf::Vector2f& Entity::getLastVelocity() const {
	return m_lastVelocity;
}