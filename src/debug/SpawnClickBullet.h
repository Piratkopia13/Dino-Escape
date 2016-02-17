#pragma once

#include <vector>

#include "../Common.h"
#include "../game/world/GameWorld.h"

class SpawnClickBullet {

public:
	SpawnClickBullet(GameWorld& world, sf::RenderWindow& window);

	void handleInput(sf::Mouse::Button button, bool isPressed) const;

private:
	GameWorld& m_world;
	sf::RenderWindow& m_window;
};
