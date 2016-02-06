#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "TileMap.h"
#include "Camera.h"
#include "enemies/Blobber.h"
#include "enemies/Effie.h"
#include "GameWorld.h"

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

	TileMap m_map;
	Camera m_camera;

	GameWorld m_world;

	Player m_player;
	Blobber m_blobber;
	Effie m_effie;

};