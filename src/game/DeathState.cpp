#include "DeathState.h"

DeathState::DeathState(StateStack& stack, Context& context)
: State(stack, context)
{

	sf::RenderWindow* window = getContext().window;

	m_bg.setFillColor(sf::Color(0, 0, 0, 0));

	m_deadText.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_deadText.setColor(sf::Color::Red);
	m_deadText.setCharacterSize(50);
	m_deadText.setString("You're a dead dino.");
	Utils::centerTextOrigin(m_deadText);

	m_restartText.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_restartText.setColor(sf::Color::White);
	m_restartText.setCharacterSize(20);
	m_restartText.setString("Press 'R' to restart level");
	Utils::centerTextOrigin(m_restartText);

	setPositions();

}

DeathState::~DeathState() {
}

void DeathState::setPositions() {

	sf::RenderWindow* window = getContext().window;

	float halfWindowWidth = window->getSize().x / 2.0f;

	m_bg.setSize(sf::Vector2f(window->getSize()));
	m_bg.setPosition(0.f, 0.f);

	m_deadText.setPosition(halfWindowWidth, 200.f);
	m_restartText.setPosition(halfWindowWidth, 300.f);


}

bool DeathState::handleEvent(const sf::Event& event) {
	
	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::R) {
			requestStackPop(); // Pop this state
			requestStackPop(); // Pop the underlying GameState
			requestStackPush(States::Game); // Create a new GameState to restart the level
		}

	} else if (event.type == sf::Event::Resized) {

		// Update text positions
		setPositions();

	}

	return true;
}

bool DeathState::update(sf::Time dt) {

	// Fade in background
	sf::Color c = m_bg.getFillColor();
	if (c.a < 200u) {
		c.a += dt.asMilliseconds() / 3u;
		std::min(c.a, static_cast<sf::Uint8>(200U)); // 200 Max value
		m_bg.setFillColor(c);
	}

	return true;
}

void DeathState::draw() {

	sf::RenderWindow* window = getContext().window;
	int width = window->getSize().x;
	int height = window->getSize().y;

	window->setView(sf::View(sf::FloatRect(0.f, 0.f, width, height)));

	window->draw(m_bg);
	window->draw(m_deadText);
	window->draw(m_restartText);


}