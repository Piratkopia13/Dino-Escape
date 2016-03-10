#pragma once

#include "../states/State.h"
#include "world/GameWorld.h"
#include "../game/world/TileMap.h"
#include "../Camera.h"
#include "HealthBar.h"

#include "../debug/SpawnClickBullet.h"
#include "../debug/SpawnClickEntity.h"

// The game state
// This is where all the magic happens
class GameState : public State {

	public:
		GameState(StateStack& stack, Context& context);

		// Handles events relevant to this state
		virtual bool handleEvent(const sf::Event& event);
		// Updates the state
		virtual bool update(sf::Time dt);
		// Draws the state
		virtual void draw();

	private:
		// Cameras for the world and head-up display (HUD)
		// The HUD shows the healthbar and status texts
		Camera m_worldCamera, m_hudCamera;

		// Status texts
		// These are mainly used for debugging and performance testing purposes
		sf::Text m_FPStext,
			m_entityCountText,
			m_particleCountText;
		bool m_showDebugTexts;
		bool m_vsync;

		// Classes to allow the spawning of bullets and entities on clicks
		// These are mainly used for debugging and performance testing purposes
		SpawnClickEntity m_spawnClickEnt;
		SpawnClickBullet m_spawnClickBlt;

		// The game world
		GameWorld m_world;

		// Pointer to the vignette shader
		// Used so that i dont have to fetch it from the PostEffectManager every frame
		const sf::Shader* m_vignetteShader;
		
		// The healthbar that renders on the HUD
		HealthBar m_healthBar;

		// Flags
		bool m_isPaused;
		bool m_hasStartedDeathAnimation;
		bool m_hasFinishedDeathAnimation;

		// Timers for the death animation
		sf::Time m_timeDead;
		const sf::Time m_deathTimer;

};