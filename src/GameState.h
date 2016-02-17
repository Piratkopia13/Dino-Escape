#pragma once

#include "states\State.h"
#include "world\TileMap.h"
#include "Camera.h"

#include "debug\SpawnClickBullet.h"
#include "debug\SpawnClickEntity.h"

class GameState : public State {

	public:
		GameState(StateStack& stack, Context context);
		~GameState();

		virtual bool handleEvent(const sf::Event& event);
		virtual bool update(sf::Time dt);
		virtual void draw();

	private:
		TileMap m_map;
		Camera m_camera;
		sf::Text m_FPStext;

		SpawnClickEntity m_spawnClickEnt;
		SpawnClickBullet m_spawnClickBlt;
		GameWorld m_world;

};