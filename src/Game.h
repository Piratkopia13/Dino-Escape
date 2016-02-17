#pragma once

#include <SFML/Graphics.hpp>

#include "TextureManager.h"
#include "FontManager.h"

#include "states/StateStack.h"
#include "game/GameState.h"
#include "MenuState.h"
#include "game/DeathState.h"

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

	StateStack m_stateStack;

};