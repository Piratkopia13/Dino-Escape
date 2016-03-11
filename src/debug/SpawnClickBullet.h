#pragma once

#include <vector>

#include "../Common.h"
#include "../game/world/GameWorld.h"

// Debug class
// Spawns a bullet on a mouse click
class SpawnClickBullet {

public:
	SpawnClickBullet(GameWorld& world, sf::RenderWindow& window);

	// Fires a bullet in a random direction at the cursors world-coordinates when mouse is clicked
	void handleInput(sf::Mouse::Button button, bool isPressed) const;

private:
	// Reference to the world
	GameWorld& m_world;
	// Reference to the window
	sf::RenderWindow& m_window;
};
