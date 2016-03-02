#pragma once

#include <vector>

#include "states\State.h"

class ControlsState : public State {

public:
	ControlsState(StateStack& stack, Context& context);
	~ControlsState();

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
	// Sets positions of all rendered texts and images to fit the current window size
	void setPositions();

private:

	enum Options {
		Play,
		Controls,
		Exit
	};

	sf::RectangleShape m_bgImg;
	sf::RectangleShape m_bg;

	sf::Text m_backText;
	sf::RectangleShape m_selectedLine;

};