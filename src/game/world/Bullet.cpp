#include "Bullet.h"

Bullet::Bullet(const BulletType type, const sf::Vector2f& from, const sf::Vector2f& velocity, const Entity* owner)
: m_velocity(velocity)
, m_owner(owner)
, m_type(type)
, m_position(from)
, m_hasHit(false)
{
	// Calculate the angle based of the velocity
	// And convert it to degrees
	m_rotation = atan2f(velocity.y, velocity.x) / .0174532925f; // wierd number is pi/180
}

void Bullet::update(sf::Time dt) {

	if (hasHit())
		// The bullet has hit something, update the time is has been "dead"
		m_timeDead += dt;
	else {
		// The bullet is still flying
		// Update time alive
		m_timeAlive += dt;
		// Update the position by the velocity
		m_position += m_velocity;
	}

}


Bullet::BulletType Bullet::getType() const {
	return m_type;
}

float Bullet::getRotation() const {
	return m_rotation;
}

const sf::Vector2f& Bullet::getVelocity() const {
	return m_velocity;
}

const sf::Vector2f& Bullet::getPosition() const {
	return m_position;
}
const Entity* Bullet::getOwner() const {
	return m_owner;
}
const bool Bullet::hasHit() const {
	return m_hasHit;
}

bool Bullet::shouldLinger() const {
	// Only fireballs should linger
	return getType() == FIREBALL;
}
