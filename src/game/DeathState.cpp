#include "DeathState.h"

DeathState::DeathState(StateStack& stack, Context& context)
: State(stack, context)
{

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Set the color of the background
	// Alpha values is set in the update method
	m_bg.setFillColor(sf::Color(0, 0, 0, 0));

	// Set up the dead/title text
	Utils::createCenteredText(m_deadText, sf::Color::Red, 50, "You're a dead dino.", getContext());

	// Set up the restart text
	Utils::createCenteredText(m_restartText, sf::Color::White, 20, "Press 'R' to restart level", getContext());

	// Set the positions of all elements
	setPositions();

}

void DeathState::setPositions() {

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Store half the window's width
	float halfWindowWidth = window->getSize().x / 2.0f;

	// Set the size and position of the background
	m_bg.setSize(sf::Vector2f(window->getSize()));
	m_bg.setPosition(0.f, 0.f);

	// Set text positions
	m_deadText.setPosition(halfWindowWidth, 200.f);
	m_restartText.setPosition(halfWindowWidth, 300.f);

}

bool DeathState::handleEvent(const sf::Event& event) {
	
	// Check if a key was pressed
	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::R) {
			// R key bound to restart the game
			// I used R since it's away from the keys you control the character with so that you wont accidentally restart the moment you die

			// Pop this state
			requestStackPop();
			// Pop the underlying GameState
			requestStackPop();
			// Create a new GameState to restart the level
			requestStackPush(States::Game);
		}

	} else if (event.type == sf::Event::Resized) {

		// Update text positions
		setPositions();

	}

	return true;
}

bool DeathState::update(sf::Time dt) {

	// Fade in background

	// Get the current color
	sf::Color c = m_bg.getFillColor();
	if (c.a < 200u) {
		// Increase alpha by a factor of the delta
		c.a += dt.asMilliseconds() / 3u;
		// Make sure the value isn't larger than 200
		std::min(c.a, static_cast<sf::Uint8>(200U));
		// Update the color
		m_bg.setFillColor(c);
	}

	return true;
}

void DeathState::draw() {

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Get the window size
	int width = window->getSize().x;
	int height = window->getSize().y;

	// Update the window view to look good when the window resizes
	window->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))));

	// Render elements
	window->draw(m_bg);
	window->draw(m_deadText);
	window->draw(m_restartText);


}