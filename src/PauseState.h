#pragma once

#include <vector>

#include "states\State.h"

class PauseState : public State {

public:
	PauseState(StateStack& stack, Context& context);
	~PauseState();

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
	// Sets positions of all rendered texts and images to fit the current window size
	void setPositions();
	// Updates the position of the bar under the selected option text
	void updateSelected();
	void resumeGame();

private:

	enum Options {
		Resume,
		Quit,
		OptionsCount
	};

	sf::RectangleShape m_bg;

	sf::Text m_title;

	std::vector<sf::Text> m_optionTexts;
	sf::RectangleShape m_selectedLine;
	unsigned int m_selectedIndex;

};