#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>

#include "../states/State.h"

// The level complete state of the game
// Will show when you finish a level
// Shows statistics and allows you to go to the next level
class LevelCompleteState : public State {

public:
	LevelCompleteState(StateStack& stack, Context& context);

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
	
	// Background color
	sf::RectangleShape m_bg;

	// Title text that shows on the top of the screen
	sf::Text m_titleText;
	// Stats title that shows underneath the main title
	sf::Text m_statsTitleText;
	// Continue text that shows on the bottom of the screen
	sf::Text m_continueText;

	// Title texts for the different stats
	sf::Text m_statsTimeTitleText;
	sf::Text m_statsHealthTitleText;
	sf::Text m_statsKilledTitleText;

	// Texts for the different stats
	sf::Text m_statsTimeText;
	sf::Text m_statsHealthText;
	sf::Text m_statsKilledText;
	sf::Text m_statsScoreText;

};