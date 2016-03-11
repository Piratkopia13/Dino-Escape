#include "SpawnClickBullet.h"

SpawnClickBullet::SpawnClickBullet(GameWorld& world, sf::RenderWindow& window)
: m_window(window)
, m_world(world)
{
}

void SpawnClickBullet::handleInput(sf::Mouse::Button button, bool isPressed) const {

	// Check if the left mouse button was pressed
	if (button == sf::Mouse::Right && isPressed) {

		// Get the mouse position in game world coordinates
		sf::Vector2f pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

		// Set the bullets velocity to something random
		sf::Vector2f velocity(rand() / (float)RAND_MAX * 10.0f - 5, rand() / (float)RAND_MAX * 10.0f - 5.f);

		// Fire the bullet in the world
		m_world.getBulletSystem().fireBullet(Bullet::NORMAL, pos, velocity, nullptr);

	}


}