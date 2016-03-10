#pragma once

#include <vector>

#include "states\State.h"

// The pause state of the game
// This is the first state that shows when the game is started
class MenuState : public State {

public:
	MenuState(StateStack& stack, Context& context);

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

private:

	// Menu options to choose from
	enum Options {
		Play,
		Controls,
		Exit,
		OptionsCount
	};

	// Background shape
	sf::RectangleShape m_bg;

	// Title text and its shadow
	sf::Text m_title;
	sf::Text m_titleShadow;

	// List of texts for the options
	std::vector<sf::Text> m_optionTexts;
	// Line that renders under the currently selected option
	sf::RectangleShape m_selectedLine;
	// What option index is currently selected
	unsigned int m_selectedIndex;

};