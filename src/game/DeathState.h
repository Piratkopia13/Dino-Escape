#pragma once

#include "../states/State.h"

// The pause state of the game
// Will render on top of the GameState while the player is dead
class DeathState : public State {

public:
	DeathState(StateStack& stack, Context& context);

	// Handles events relevant to this state
	virtual bool handleEvent(const sf::Event& event);
	// Updates the state
	virtual bool update(sf::Time dt);
	// Draws the state
	virtual void draw();

private:
	// Sets positions of all rendered texts and images to fit the current window size
	void setPositions();

private:

	// Background shape, semi-transparent black
	sf::RectangleShape m_bg;
	// Title text that shows on top of the screen
	sf::Text m_deadText;
	// Restart text that shows at the bottom of the screen
	sf::Text m_restartText;

};