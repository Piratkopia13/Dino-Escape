#pragma once

#include <vector>

#include "states\State.h"

// The controls state of the game
// Will show what controls do what
class ControlsState : public State {

public:
	ControlsState(StateStack& stack, Context& context);

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

	// Background color rendered over the main menu to hide it
	sf::RectangleShape m_bg;
	// Background image showing the controls
	sf::RectangleShape m_bgImg;

	// Back text/button that shows at the bottom of the screen
	sf::Text m_backText;
	// Line that renders under the currently selected option
	sf::RectangleShape m_selectedLine;

};