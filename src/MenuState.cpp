#include "MenuState.h"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
{

	m_text.setFont(context.fonts->get(FontManager::Roboto));
	m_text.setCharacterSize(80);
	m_text.setColor(sf::Color::Green);
	m_text.setString("Dino Escape");

	m_text.setPosition(420, 280);

}

MenuState::~MenuState() {
}

bool MenuState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPush(States::Game);
	}

	return true;
}

bool MenuState::update(sf::Time dt) {
	
	return true;
}

void MenuState::draw() {

	getContext().window->draw(m_text);

}
