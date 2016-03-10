#include "PauseState.h"

PauseState::PauseState(StateStack& stack, Context& context)
: State(stack, context)
, m_optionTexts(OptionsCount) // Initalize empty sf::Text instances
{

	// Set the color of the selectedLine
	m_selectedLine.setFillColor(sf::Color(47, 181, 72, 255));
	// Set the default selected index to the resume button
	m_selectedIndex = Options::Resume;

	// Set up the title
	Utils::createCenteredText(m_title, sf::Color(61, 212, 100, 255), 60,
		"Paused", getContext());

	// Set the background color to a semi-transparent black
	m_bg.setFillColor(sf::Color(0, 0, 0, 113));

	// Set up the resume button
	Utils::createCenteredText(m_optionTexts[Resume], sf::Color::White, 35,
		"Resume", getContext());

	// Set up the restart button
	Utils::createCenteredText(m_optionTexts[RestartLevel], sf::Color::White, 35,
		"Restart Level", getContext());

	// Set up the quit button
	Utils::createCenteredText(m_optionTexts[Quit], sf::Color::White, 35,
		"Quit", getContext());

	// Pause the music
	getContext().music->setPaused(true);

	// Set the positions of all elements
	setPositions();

	// Update the position and size of the selectedLine
	updateSelected();

}

bool PauseState::handleEvent(const sf::Event& event) {

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
			case Options::Resume:
				// Resume game
				resumeGame();
				break;
			case Options::RestartLevel:
				// Pop this state
				requestStackPop();
				// Pop the underlying GameState
				requestStackPop();
				// Create a new GameState to restart the level
				requestStackPush(States::Game);
				break;
			case Options::Quit:
				// Clear the stack and quit the game
				requestStackClear();
				break;
			}

		} else if (event.key.code == sf::Keyboard::Escape) {
			// Escape key bound to resume the game
			resumeGame();
		}

	} else if (event.type == sf::Event::Resized) {

		// Update text positions
		setPositions();
		updateSelected();

	}

	// Allow underlying states to handle events while pause is active
	return true;

}

void PauseState::resumeGame() {

	// Pop this state
	requestStackPop();
	// Resume the music
	getContext().music->setPaused(false);

}

bool PauseState::update(sf::Time dt) {

	// Dont allow underlaying states to update while pause is active
	return false;

}

void PauseState::draw() {

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Get the window size
	int width = window->getSize().x;
	int height = window->getSize().y;

	// Update the window view to look good when the window resizes
	window->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))));

	// Render elements
	window->draw(m_bg);
	window->draw(m_title);

	for (auto& text : m_optionTexts)
		window->draw(text);

	window->draw(m_selectedLine);

}

void PauseState::updateSelected() {

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

void PauseState::setPositions() {

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

	// Set the size and position of the background
	m_bg.setSize(sf::Vector2f(window->getSize()));
	m_bg.setPosition(0.f, 0.f);

	// Update positions for options texts
	Utils::centerTextOrigin(m_optionTexts[Resume]);
	m_optionTexts[Resume].setPosition(halfWindowWidth, 300.f);

	Utils::centerTextOrigin(m_optionTexts[RestartLevel]);
	m_optionTexts[RestartLevel].setPosition(halfWindowWidth, 400.f);

	Utils::centerTextOrigin(m_optionTexts[Quit]);
	m_optionTexts[Quit].setPosition(halfWindowWidth, 500.f);


}