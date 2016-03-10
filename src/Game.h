#pragma once

#include "Common.h"

#include "TextureManager.h"
#include "FontManager.h"
#include "LevelManager.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
#include "PostEffectManager.h"

#include "states/StateStack.h"
#include "game/GameState.h"
#include "MenuState.h"
#include "ControlsState.h"
#include "game/DeathState.h"
#include "game/LevelCompleteState.h"
#include "PauseState.h"

#include "debug/DebugRenderer.h"

// Starting point of the game
class Game {

	public:
		Game();

		// Runs the game
		void run();

		// Returns the current FPS
		static int getFPS();

	public:
		// The fixed delta time for every update
		const sf::Time TimePerUpdate;

	private:
		// Register the different states
		void registerStates();

		// Parts of the game loop
		void processEvents();
		void update(sf::Time dt);
		void render();

private:
	// The RenderWindow
	sf::RenderWindow m_window;
	// Current FPS
	static int m_fps;

	// Things all states needs to be able to access
	// Will be passed by pointers to the context
	TextureManager m_textureManager;
	FontManager m_fontManager;
	LevelManager m_levelManager;
	MusicPlayer m_musicPlayer;
	SoundPlayer m_soundPlayer;
	PostEffectManager m_postEffectManager;

	// The stack of states
	StateStack m_stateStack;

};