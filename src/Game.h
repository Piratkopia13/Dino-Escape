#pragma once

#include "Common.h"

#include "TextureManager.h"
#include "FontManager.h"
#include "LevelManager.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"

#include "states/StateStack.h"
#include "game/GameState.h"
#include "MenuState.h"
#include "game/DeathState.h"
#include "game/LevelCompleteState.h"
#include "PauseState.h"

#include "debug/DebugRenderer.h"

class Game {

	public:
		Game();
		void run();
		static int getFPS();

	public:
		const sf::Time TimePerFrame;

	private:
		void registerStates();

		void processEvents();
		void update(sf::Time dt);
		void render();

private:
	sf::RenderWindow m_window;
	static int m_fps;

	TextureManager m_textureManager;
	FontManager m_fontManager;
	LevelManager m_levelManager;
	MusicPlayer m_musicPlayer;
	SoundPlayer m_soundPlayer;

	StateStack m_stateStack;

};