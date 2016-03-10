#include "ControlsState.h"

ControlsState::ControlsState(StateStack& stack, Context& context)
: State(stack, context)
{

	// Set the color of the selectedLine
	m_selectedLine.setFillColor(sf::Color(47, 181, 72, 255));

	// Set up the background texture
	m_bgImg.setTexture(&getContext().textures->get(Textures::ID::ControlsBackground));
	// Set up the background color
	m_bg.setFillColor(sf::Color(2, 23, 33, 255));

	// Set up back button
	Utils::createCenteredText(m_backText, sf::Color::White, 35, 
		"Back", getContext());

	// Set the width of the selectedLine to the width of the currently selected option
	sf::Vector2f lineSize(m_backText.getLocalBounds().width, 4.0f);
	m_selectedLine.setSize(lineSize);
	// Set the origin to the center of the line
	m_selectedLine.setOrigin(lineSize.x / 2.0f, lineSize.y / 2.0f);
	
	// Set the positions of all elements
	setPositions();

}

bool ControlsState::handleEvent(const sf::Event& event) {

	// Check if a key was pressed
	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape)
			// Enter key bound to the back button, escape button bound to exit the state
			// Pop this state
			requestStackPop();

	} else if (event.type == sf::Event::Resized) {

		// Update text positions
		setPositions();

	}

	// Dont allow underlaying states to handle events
	return false;
}

bool ControlsState::update(sf::Time dt) {

	// Dont allow underlaying states to update
	return false;
}

void ControlsState::draw() {

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Render elements
	window->draw(m_bg);
	window->draw(m_bgImg);
	window->draw(m_backText);
	window->draw(m_selectedLine);

}

void ControlsState::setPositions() {

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Get the window size
	int width = window->getSize().x;
	int height = window->getSize().y;

	// Update the window view to look good when the window resizes
	window->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))));

	// Store half the window's width
	float halfWindowWidth = width / 2.0f;

	int imgWidth = m_bgImg.getTexture()->getSize().x;
	int imgHeight = m_bgImg.getTexture()->getSize().y;
	float aspectRatio = (float)imgWidth / imgHeight;

	m_bgImg.setSize(sf::Vector2f(height * aspectRatio, static_cast<float>(height)));
	m_bgImg.setPosition(halfWindowWidth - m_bgImg.getSize().x / 2.f, 0.f);

	m_bg.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));


	// Update positions for back text
	Utils::centerTextOrigin(m_backText);
	m_backText.setPosition(halfWindowWidth, height - 50.f);

	// Set the position of the selectedLine
	m_selectedLine.setPosition(halfWindowWidth, height - 50.f + m_backText.getGlobalBounds().height);


}