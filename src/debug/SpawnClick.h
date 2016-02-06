#pragma once

#include <vector>
#include "../GameWorld.h"
#include "../enemies/Blobber.h"
#include "../enemies/Effie.h"

class SpawnClick {

	public:
		enum EnemyType {
			NONE,
			BLOBBER,
			EFFIE
		};

	public:
		SpawnClick(GameWorld& world, sf::RenderWindow& window);
		~SpawnClick();

		void setSpawnType(EnemyType type);
		void handleInput(sf::Mouse::Button button, bool isPressed);

	private:
		GameWorld& m_world;
		EnemyType m_type;
		std::vector<Entity*> m_entites;
		sf::RenderWindow& m_window;
};
