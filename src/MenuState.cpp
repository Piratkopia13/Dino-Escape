#include "MenuState.h"

MenuState::MenuState(StateStack& stack, Context& context)
: State(stack, context)
, m_optionTexts(OptionsCount) // Initalize empty sf::Text instances
{

	// Set the color of the selectedLine
	m_selectedLine.setFillColor(sf::Color(47, 181, 72, 255));
	// Set the default selected index to the play button
	m_selectedIndex = Options::Play;

	// Set up the title
	Utils::createCenteredText(m_title, sf::Color(61, 212, 100, 255), 80,
		"Dino Escape", getContext());

	// Set up the title shadow to be the same as the title, but semi-transparent black
	// Offset is added in the setPositions() method
	m_titleShadow = m_title;
	m_titleShadow.setColor(sf::Color(0, 0, 0, 200));

	// Set up the version number text
	Utils::createText(m_version, sf::Color::White, 15, getContext().versionText, getContext());

	// Set up background texture
	m_bg.setTexture(&getContext().textures->get(Textures::ID::MenuBackground));

	// Set up the play button
	Utils::createCenteredText(m_optionTexts[Play], sf::Color::White, 35,
		"Play", getContext());

	// Set up the controls button
	Utils::createCenteredText(m_optionTexts[Controls], sf::Color::White, 35,
		"Controls", getContext());

	// Set up the exit button
	Utils::createCenteredText(m_optionTexts[Exit], sf::Color::White, 35,
		"Exit", getContext());

	// Set the positions of all elements
	setPositions();

	// Update the position and size of the selectedLine
	updateSelected();

	// Play the menu theme
	getContext().music->play(Music::ID::MenuTheme);

}

bool MenuState::handleEvent(const sf::Event& event) {

	// Check if a key was pressed
	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::Up) {
			// Up arrow key bound to go up in the list

			if (m_selectedIndex > 0)
				m_selectedIndex--;
			else
				m_selectedIndex = m_optionTexts.size() - 1;

			updateSelected();

		} else if (event.key.code == sf::Keyboard::Down) {
			// Down arrow key bound to go down in the list

			if (m_selectedIndex < m_optionTexts.size() - 1)
				m_selectedIndex++;
			else
				m_selectedIndex = 0;

			updateSelected();

		} else if (event.key.code == sf::Keyboard::Return) {
			// Enter key bound to press the selected button

			switch (m_selectedIndex) {
			case Options::Play:
				// Pop the current state
				requestStackPop();
				// Push the GameState to start the level
				requestStackPush(States::Game);
				break;
			case Options::Controls:
				// Push the ControlsState
				requestStackPush(States::Controls);
				break;
			case Options::Exit:
				// Pop this state, which should be the last one
				requestStackPop();
				break;
			}

		}

	} else if (event.type == sf::Event::Resized) {

		// Update text positions
		setPositions();
		updateSelected();

	}

	return true;
}

bool MenuState::update(sf::Time dt) {
	
	// Allow underlying states to update
	// This does not matter since it is the bottom layer
	return true;
}

void MenuState::draw() {

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Get the window size
	int width = window->getSize().x;
	int height = window->getSize().y;

	// Update the window view to look good when the window resizes
	window->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))));

	// Render elements
	window->draw(m_bg);
	window->draw(m_titleShadow);
	window->draw(m_title);
	window->draw(m_version);

	for (auto& text : m_optionTexts) {
		window->draw(text);
	}

	window->draw(m_selectedLine);

}

void MenuState::updateSelected() {

	// Play select sound
	getContext().sounds->play(Sounds::Select);

	// Set the width of the selectedLine to the width of the currently selected option
	sf::Vector2f lineSize(m_optionTexts.at(m_selectedIndex).getLocalBounds().width, 4.0f);

	m_selectedLine.setSize(lineSize);

	// Set the origin to the center of the line
	m_selectedLine.setOrigin(lineSize.x / 2.0f, lineSize.y / 2.0f);

	// Set the position to under the currently selected option
	const sf::Vector2f& optionPosition = m_optionTexts.at(m_selectedIndex).getPosition();
	m_selectedLine.setPosition(optionPosition.x, optionPosition.y + m_optionTexts.at(m_selectedIndex).getGlobalBounds().height);

}

void MenuState::setPositions() {

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Get the window size
	int width = window->getSize().x;
	int height = window->getSize().y;

	// Store half the window's width
	float halfWindowWidth = window->getSize().x / 2.0f;

	// Set the position of the title
	m_title.setPosition(halfWindowWidth, 150);
	Utils::centerTextOrigin(m_title);

	// Set the position of the version text
	m_version.setPosition(0.f, height - 20.f);

	// Set the position of the title shadow
	m_titleShadow.setPosition(halfWindowWidth + 8, 158);


	// Set background size depending on window size to keep image aspect ratio
	int imgWidth = m_bg.getTexture()->getSize().x;
	int imgHeight = m_bg.getTexture()->getSize().y;
	float aspectRatio = imgHeight / (float)imgWidth;

	if (height < width * aspectRatio)
		m_bg.setSize(sf::Vector2f(static_cast<float>(width), width * aspectRatio));
	else
		m_bg.setSize(sf::Vector2f(height * (1.f / aspectRatio), static_cast<float>(height)));
	m_bg.setPosition(0, 0);


	// Update positions for options texts
	Utils::centerTextOrigin(m_optionTexts[Play]);
	m_optionTexts[Play].setPosition(halfWindowWidth, 300);

	Utils::centerTextOrigin(m_optionTexts[Controls]);
	m_optionTexts[Controls].setPosition(halfWindowWidth, 400);

	Utils::centerTextOrigin(m_optionTexts[Exit]);
	m_optionTexts[Exit].setPosition(halfWindowWidth, 500);


}