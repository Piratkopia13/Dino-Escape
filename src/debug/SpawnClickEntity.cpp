#include "SpawnClickEntity.h"

SpawnClickEntity::SpawnClickEntity(GameWorld& world, sf::RenderWindow& window)
: m_world(world)
, m_type(NONE)
, m_window(window)
{
}

void SpawnClickEntity::handleInput(sf::Mouse::Button button, bool isPressed) {

	if (button == sf::Mouse::Left && isPressed) {

		sf::Vector2f pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

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