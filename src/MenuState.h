#pragma once

#include <vector>

#include "states\State.h"

class MenuState : public State {

public:
	MenuState(StateStack& stack, Context context);
	~MenuState();

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
	void updateSelected();

private:

	enum Options {
		Play,
		Controls,
		Exit
	};

	sf::RectangleShape m_bg;

	sf::Text m_title;
	sf::Text m_titleShadow;

	std::vector<sf::Text> m_optionTexts;
	sf::RectangleShape m_selectedLine;
	unsigned int m_selectedIndex;

};