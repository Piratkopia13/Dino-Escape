#pragma once

#include <memory>
#include "../Common.h"
#include "StateIdentifiers.h"
#include "../TextureManager.h"
#include "../FontManager.h"
#include "../LevelManager.h"
#include "../MusicPlayer.h"
#include "../SoundPlayer.h"

// Forward declare the StateStack
class StateStack;

// Base class for all states
class State {

	public:
		typedef std::unique_ptr<State> Ptr;

	public:
		State(StateStack& stack, Context& context);
		virtual ~State();

		// Draws the state
		virtual void draw() = 0;
		// Updates the state
		virtual bool update(sf::Time dt) = 0;
		// Handles events for the state
		virtual bool handleEvent(const sf::Event& event) = 0;

	protected:
		// Request the push of a new state to the stack next update
		void requestStackPush(States::ID stateID);
		// Request to pop the top state in the stack next update
		void requestStackPop();
		// Request to clear the stack in the next update
		void requestStackClear();

		// Returns the context owned by the stack
		Context& getContext();

	private:
		// Pointer to the stack
		StateStack* m_stack;
		// Reference to the context owned by the stack
		Context& m_context;

};