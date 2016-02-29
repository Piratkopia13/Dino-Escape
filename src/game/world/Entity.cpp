#include "Entity.h"
#include "../Player.h"
#include "../world/GameWorld.h"

Entity::Entity()
// Set up default values
: m_flashTime(sf::seconds(.2f))
, invulnerableTime(sf::seconds(.01f))
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

	// Update timers
	m_hitFlashTimer += dt;
	m_invulnerableTimer += dt;

	// Set color to normal if timer has expired
	if (m_hitFlashTimer >= m_flashTime)
		sprite.setColor(sf::Color(255, 255, 255, 255));

	// Update the animation
	if (currentAnimation != nullptr)
		sprite.play(*currentAnimation);
	sprite.update(dt);


};

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// Draw the sprite
	target.draw(sprite, states);
}

void Entity::hitByBullet(Bullet* blt) {

	// TODO : make different bullet-types do different amount of damage

	sf::Vector2f pushBack(blt->getVelocity() * hitByBulletXMultiplier);
	pushBack.y -= hitByBulletJumpValue;
	damage(1, pushBack);

	if (getHealth() <= 0) {
		// Check if the level stats has to be updated / player killed an enemy
		if (blt->getOwner() == getGameWorld().getPlayer())
			getGameWorld().playerKilledEntity();
	}

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
	
	if (m_invulnerableTimer >= invulnerableTime) {

		// Reset timer
		m_invulnerableTimer = sf::Time::Zero;

		// Update health
		m_health -= value;

		if (getHealth() <= 0) {
			// Tell GameWorld to remove this entity
			m_isDead = true;
			// Add a particle system from the current animation frame
			m_world->addParticleSystem(getCenterPos(), sprite.copyTextureToImage(), sprite.getTextureRect(), sprite.getScale());
			// Reset velocity
			stopMoving();
		}

		// Play hit sound
		if (dynamic_cast<Player*>(this))
			m_world->getContext().sounds->play(Sounds::HitPlayer, getCenterPos());
		else
			m_world->getContext().sounds->play(Sounds::HitEnemy, getCenterPos());

		// Reset flash timer
		m_hitFlashTimer = sf::Time::Zero;
		// Change color
		sprite.setColor(sf::Color(255, 150, 150, 255));
	
	}
}
void Entity::damage(const int value, const sf::Vector2f pushBack) {
	
	if (m_invulnerableTimer >= invulnerableTime) {
	
		// Reset velocity
		stopMoving();

		// Push the entitiy back
		velocity += pushBack;
	
	}

	damage(value);

}
void Entity::destroy() {
	m_health = 0;
	m_isDead = true;
}
void Entity::setVelocity(const sf::Vector2f& velocity) {
	this->velocity = velocity;
}
void Entity::stopMoving() {
	velocity.x = 0.f;
	velocity.y = 0.f;
	m_lastVelocity.x = 0.f;
	m_lastVelocity.y = 0.f;
}

GameWorld& Entity::getGameWorld() const {
	return *m_world;
}
int Entity::getHealth() const {
	return m_health;
}
bool Entity::isDead() const {
	return m_isDead;
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
