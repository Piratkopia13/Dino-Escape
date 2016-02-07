#include "SpawnClickBullet.h"

SpawnClickBullet::SpawnClickBullet(GameWorld& world, sf::RenderWindow& window)
: m_window(window)
, m_world(world)
{
	srand(time(0));
}

void SpawnClickBullet::handleInput(sf::Mouse::Button button, bool isPressed) const {

	if (button == sf::Mouse::Right && isPressed) {

		sf::Vector2f pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		sf::Vector2f velocity(rand() / (float)RAND_MAX * 10.0f - 5, rand() / (float)RAND_MAX * 10.0f - 5.f);

		m_world.getBulletSystem().fireBullet(Bullet::NORMAL, pos, velocity, nullptr);

	}


}