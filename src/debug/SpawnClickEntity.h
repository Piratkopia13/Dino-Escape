#pragma once

#include <vector>

#include "../Common.h"
#include "../game/world/GameWorld.h"
#include "../game/enemies/Blobber.h"
#include "../game/enemies/Effie.h"

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
