#include "DeathState.h"

DeathState::DeathState(StateStack& stack, Context context)
: State(stack, context)
{

	sf::RenderWindow* window = getContext().window;

	m_bg.setSize(sf::Vector2f(window->getSize()));
	m_bg.setFillColor(sf::Color(0, 0, 0, 200));

	m_deadText.setFont(getContext().fonts->get(FontManager::Emulogic));
	m_deadText.setColor(sf::Color::Red);
	m_deadText.setCharacterSize(50);
	m_deadText.setString("You're a dead dino.");
	Utils::centerTextOrigin(m_deadText);
	m_deadText.setPosition(window->getSize().x / 2.0f, 200.f);

	m_restartText.setFont(getContext().fonts->get(FontManager::Emulogic));
	m_restartText.setColor(sf::Color::White);
	m_restartText.setCharacterSize(20);
	m_restartText.setString("Press R to come back from the dead");
	Utils::centerTextOrigin(m_restartText);
	m_restartText.setPosition(window->getSize().x / 2.0f, 300.f);


}

DeathState::~DeathState() {
}

bool DeathState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::R) {
			requestStackPop();
		}

	}

	return false;
}

bool DeathState::update(sf::Time dt) {

	return false;
}

void DeathState::draw() {

	sf::RenderWindow* window = getContext().window;

	window->draw(m_bg);
	window->draw(m_deadText);
	window->draw(m_restartText);


}