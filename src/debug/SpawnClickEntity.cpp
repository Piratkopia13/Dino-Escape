#include "SpawnClickEntity.h"

SpawnClickEntity::SpawnClickEntity(GameWorld& world, sf::RenderWindow& window)
: m_world(world)
, m_type(NONE)
, m_window(window)
{
}

void SpawnClickEntity::handleInput(sf::Mouse::Button button, bool isPressed) {

	// Check if the left mouse button was pressed
	if (button == sf::Mouse::Left && isPressed) {

		// Get the mouse position in game world coordinates
		sf::Vector2f pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

		// Spawn a new entity depending on the chosen type
		switch (m_type) {
		case SpawnClickEntity::BLOBBER:

			m_world.add(new Blobber(m_world, pos));

			break;
		case SpawnClickEntity::EFFIE:
			
			m_world.add(new Effie(m_world, pos));

			break;
		}

	}

}

void SpawnClickEntity::setSpawnType(EnemyType type) {
	m_type = type;
}