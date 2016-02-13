#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "world/TileMap.h"
#include "Camera.h"
#include "enemies/Blobber.h"
#include "enemies/Effie.h"
#include "world/GameWorld.h"

#include "debug/DebugRenderer.h"
#include "debug/SpawnClickEntity.h"
#include "debug/SpawnClickBullet.h"

class Game {

	public:
		Game();
		void run();

	public:
		const sf::Time TimePerFrame;

	private:
		void processEvents();
		void update(sf::Time dt);
		void render();

private:
	sf::RenderWindow m_window;
	int m_fps;

	TileMap m_map;
	Camera m_camera;

	GameWorld m_world;

	Entity::EntityPtr m_player;

	sf::Font m_font;
	sf::Text m_FPStext;
	sf::Text m_posText;

	sf::RectangleShape debugBB;
	SpawnClickEntity m_spawnClickEnt;
	SpawnClickBullet m_spawnClickBlt;

};