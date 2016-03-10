#pragma once

#include <vector>

#include "states\State.h"

// The pause state of the game
// Will show when you press escape while in the game state
class PauseState : public State {

public:
	PauseState(StateStack& stack, Context& context);

	// Handles events relevant to this state
	virtual bool handleEvent(const sf::Event& event);
	// Updates the state
	virtual bool update(sf::Time dt);
	// Draws the state
	virtual void draw();

private:
	// Sets positions of all rendered texts and images to fit the current window size
	void setPositions();
	// Updates the position of the bar under the selected option text
	void updateSelected();
	// Removes this state from the statestack and resumes the game
	void resumeGame();

private:

	// Menu options to choose from
	enum Options {
		Resume,
		RestartLevel,
		Quit,
		OptionsCount
	};

	// Background shape, semi-transparent black
	sf::RectangleShape m_bg;

	// Title text that shows on the top of the screen
	sf::Text m_title;

	// List of texts for the options
	std::vector<sf::Text> m_optionTexts;
	// Line that renders under the currently selected option
	sf::RectangleShape m_selectedLine;
	// What option index is currently selected
	unsigned int m_selectedIndex;

};