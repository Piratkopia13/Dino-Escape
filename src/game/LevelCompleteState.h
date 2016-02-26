#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>

#include "../states/State.h"

class LevelCompleteState : public State {

public:
	LevelCompleteState(StateStack& stack, Context& context);
	~LevelCompleteState();

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
	// Sets positions of all rendered texts and images to fit the current window size
	void setPositions();

private:
	LevelManager::Stats m_stats;

	sf::RectangleShape m_bg;
	sf::Text m_titleText;
	sf::Text m_continueText;
	sf::Text m_statsTitleText;

	sf::Text m_statsTimeTitleText;
	sf::Text m_statsHealthTitleText;
	sf::Text m_statsKilledTitleText;

	sf::Text m_statsTimeText;
	sf::Text m_statsHealthText;
	sf::Text m_statsKilledText;
	sf::Text m_statsScoreText;

};