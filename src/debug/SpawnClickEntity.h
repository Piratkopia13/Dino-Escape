#pragma once

#include <vector>
#include "../world/GameWorld.h"
#include "../enemies/Blobber.h"
#include "../enemies/Effie.h"

class SpawnClickEntity {

	public:
		enum EnemyType {
			NONE,
			BLOBBER,
			EFFIE
		};

	public:
		SpawnClickEntity(GameWorld& world, sf::RenderWindow& window);

		void setSpawnType(EnemyType type);
		void handleInput(sf::Mouse::Button button, bool isPressed);

	private:
		GameWorld& m_world;
		EnemyType m_type;
		sf::RenderWindow& m_window;
};
