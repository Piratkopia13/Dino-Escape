#pragma once

#include <vector>

#include "../Common.h"
#include "../game/world/GameWorld.h"
#include "../game/enemies/Blobber.h"
#include "../game/enemies/Effie.h"

// Debug class
// Spawns a chosen entity on a mouse click
class SpawnClickEntity {

	public:
		// All the different types of enemies that are available to spawn
		enum EnemyType {
			NONE,
			BLOBBER,
			EFFIE
		};

	public:
		SpawnClickEntity(GameWorld& world, sf::RenderWindow& window);

		// Sets the type of enemy that will spawn on a click
		void setSpawnType(EnemyType type);
		// Spawns the enemy at the cursors world-coordinates when mouse is clicked
		void handleInput(sf::Mouse::Button button, bool isPressed);

	private:
		// Reference to the world
		GameWorld& m_world;
		// The type of the enemy
		EnemyType m_type;
		// Reference to the window
		sf::RenderWindow& m_window;
};
