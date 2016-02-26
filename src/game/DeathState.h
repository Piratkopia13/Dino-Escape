#pragma once

#include "../states/State.h"

class DeathState : public State {

public:
	DeathState(StateStack& stack, Context& context);
	~DeathState();

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
	// Sets positions of all rendered texts and images to fit the current window size
	void setPositions();

private:
	sf::RectangleShape m_bg;
	sf::Text m_deadText;
	sf::Text m_restartText;

};