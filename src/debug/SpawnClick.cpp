#include "SpawnClick.h"

SpawnClick::SpawnClick(GameWorld& world, sf::RenderWindow& window)
: m_world(world)
, m_type(NONE)
, m_window(window)
{
}

SpawnClick::~SpawnClick() {

	for (Entity* e : m_entites)
		delete e;

}

void SpawnClick::handleInput(sf::Mouse::Button button, bool isPressed) {

	if (button == sf::Mouse::Left && isPressed) {

		sf::Vector2f pos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

		switch (m_type) {
		case SpawnClick::BLOBBER:

			m_entites.push_back(new Blobber(pos));
			m_world.add(m_entites.back());

			break;
		case SpawnClick::EFFIE:

			m_entites.push_back(new Effie(pos));
			m_world.add(m_entites.back());

			break;
		}

	}

}

void SpawnClick::setSpawnType(EnemyType type) {
	m_type = type;
}