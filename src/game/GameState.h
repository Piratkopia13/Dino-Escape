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
			m_entityCountText,
			m_particleCountText;
		bool m_showDebugTexts;
		bool m_vsync;

		SpawnClickEntity m_spawnClickEnt;
		SpawnClickBullet m_spawnClickBlt;
		GameWorld m_world;

		const sf::Shader* m_vignetteShader;
		
		HealthBar m_healthBar;

		bool m_isPaused;
		bool m_hasStartedDeathAnimation;
		bool m_hasFinishedDeathAnimation;

		sf::Time m_timeDead;
		const sf::Time m_deathTimer;

};