#pragma once

#include "states\State.h"

class MenuState : public State {

public:
	MenuState(StateStack& stack, Context context);
	~MenuState();

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
	sf::Text m_text;

};