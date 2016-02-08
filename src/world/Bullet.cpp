#include "Bullet.h"

Bullet::Bullet(const BulletType type, const sf::Vector2f& from, const sf::Vector2f& velocity, const Entity* owner)
: m_velocity(velocity)
, m_owner(owner)
, m_type(type)
, m_position(from)
{
	m_rotation = atan2f(velocity.y, velocity.x) / .0174532925f; // wierd number is pi/180
	
	//sf::RectangleShape shape;
	//shape.setPosition(from);

	//switch (type) {
	//case Bullet::NORMAL:
	//	shape.setFillColor(sf::Color::Yellow);
	//	shape.setSize(sf::Vector2f(2.f, 2.f));
	//	break;
	//case Bullet::FIREBALL:
	//	shape.setFillColor(sf::Color::Red);
	//	shape.setSize(sf::Vector2f(2.f, 2.f));
	//	break;
	//default:
	//	shape.setFillColor(sf::Color::White);
	//	shape.setSize(sf::Vector2f(2.f, 2.f));
	//	break;
	//}

	//m_shape = shape;

}
Bullet::~Bullet() {
}

void Bullet::update(sf::Time dt) {

	m_timeAlive += dt;
	m_position += m_velocity;
	//m_shape.move(m_velocity);

}

//void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//
//	target.draw(m_shape);
//
//}

Bullet::BulletType Bullet::getType() const {
	return m_type;
}

float Bullet::getRotation() const {
	return m_rotation;
}

//sf::FloatRect Bullet::getGlobalBounds() {
//	return m_shape.getGlobalBounds();
//}
const sf::Vector2f& Bullet::getPosition() const {
	return m_position;
}
const Entity* Bullet::getOwner() const {
	return m_owner;
}