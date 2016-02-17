#include "Bullet.h"

Bullet::Bullet(const BulletType type, const sf::Vector2f& from, const sf::Vector2f& velocity, const Entity* owner)
: m_velocity(velocity)
, m_owner(owner)
, m_type(type)
, m_position(from)
{
	m_rotation = atan2f(velocity.y, velocity.x) / .0174532925f; // wierd number is pi/180
}
Bullet::~Bullet() {
}

void Bullet::update(sf::Time dt) {

	m_timeAlive += dt;
	m_position += m_velocity;

}


Bullet::BulletType Bullet::getType() const {
	return m_type;
}

float Bullet::getRotation() const {
	return m_rotation;
}

const sf::Vector2f& Bullet::getPosition() const {
	return m_position;
}
const Entity* Bullet::getOwner() const {
	return m_owner;
}