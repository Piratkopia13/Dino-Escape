#pragma once

#include "../states/State.h"
#include "../game/world/TileMap.h"
#include "../Camera.h"
#include "HealthBar.h"

#include "../debug/SpawnClickBullet.h"
#include "../debug/SpawnClickEntity.h"

class GameState : public State {

	public:
		GameState(StateStack& stack, Context& context);
		~GameState();

		virtual bool handleEvent(const sf::Event& event);
		virtual bool update(sf::Time dt);
		virtual void draw();

	private:
		TileMap m_map;
		Camera m_worldCamera, m_hudCamera;
		sf::Text m_FPStext,
			m_entityCountText;

		SpawnClickEntity m_spawnClickEnt;
		SpawnClickBullet m_spawnClickBlt;
		GameWorld m_world;
		
		HealthBar m_healthBar;

};