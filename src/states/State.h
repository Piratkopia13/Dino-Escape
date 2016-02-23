#pragma once

#include <memory>
#include "../Common.h"
#include "StateIdentifiers.h"
#include "../TextureManager.h"
#include "../FontManager.h"
#include "../LevelManager.h"
#include "../MusicPlayer.h"
#include "../SoundPlayer.h"

class StateStack;

class State {

	public:
		typedef std::unique_ptr<State> Ptr;
		struct Context {
			Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts, LevelManager& levels, MusicPlayer& music, SoundPlayer& sounds);

			sf::RenderWindow* window;
			TextureManager* textures;
			FontManager* fonts;
			LevelManager* levels;
			MusicPlayer* music;
			SoundPlayer* sounds;
		};

	public:
		State(StateStack& stack, Context& context);
		virtual ~State();

		virtual void draw() = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(const sf::Event& event) = 0;

	protected:
		void requestStackPush(States::ID stateID);
		void requestStackPop();
		void requestStackClear();

		Context& getContext();

	private:
		StateStack* m_stack;
		Context& m_context;

};