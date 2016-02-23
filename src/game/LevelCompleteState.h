#pragma once

#include "../states/State.h"

class LevelCompleteState : public State {

public:
	LevelCompleteState(StateStack& stack, Context& context);
	~LevelCompleteState();

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
	sf::RectangleShape m_bg;
	sf::Text m_titleText;
	sf::Text m_continueText;
	sf::Text m_statsTitleText;
	sf::Text m_statsText;

};