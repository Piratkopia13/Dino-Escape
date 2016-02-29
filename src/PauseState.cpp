#include "PauseState.h"

PauseState::PauseState(StateStack& stack, Context& context)
: State(stack, context)
, m_optionTexts(OptionsCount)
{

	m_selectedLine.setFillColor(sf::Color(47, 181, 72, 255));
	m_selectedIndex = Options::Resume;

	Utils::createCenteredText(m_title, sf::Color(61, 212, 100, 255), 60,
		"Paused", getContext());

	m_bg.setFillColor(sf::Color(0, 0, 0, 113));

	Utils::createCenteredText(m_optionTexts[Resume], sf::Color::White, 35,
		"Resume", getContext());

	Utils::createCenteredText(m_optionTexts[RestartLevel], sf::Color::White, 35,
		"Restart Level", getContext());

	Utils::createCenteredText(m_optionTexts[Quit], sf::Color::White, 35,
		"Quit", getContext());

	// Pause music
	getContext().music->setPaused(true);

	setPositions();

	updateSelected();

}

PauseState::~PauseState() {
}

bool PauseState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::Up) {
			if (m_selectedIndex > 0)
				m_selectedIndex--;
			else
				m_selectedIndex = m_optionTexts.size() - 1;

			updateSelected();

		} else if (event.key.code == sf::Keyboard::Down) {
			if (m_selectedIndex < m_optionTexts.size() - 1)
				m_selectedIndex++;
			else
				m_selectedIndex = 0;

			updateSelected();

		} else if (event.key.code == sf::Keyboard::Return) {

			switch (m_selectedIndex) {
			case Options::Resume:
				// Resume game
				resumeGame();
				break;
			case Options::RestartLevel:
				requestStackPop(); // Pop this state
				requestStackPop(); // Pop the underlying GameState
				requestStackPush(States::Game); // Create a new GameState to restart the level
				break;
			case Options::Quit:
				// Clear the stack and quit the game
				requestStackClear();
				break;
			}

		} else if (event.key.code == sf::Keyboard::Escape) {
			// Resume game
			resumeGame();
		}

	} else if (event.type == sf::Event::Resized) {

		// Update text positions
		setPositions();
		updateSelected();

	}

	return true;
}

void PauseState::resumeGame() {
	requestStackPop();
	getContext().music->setPaused(false);
}

bool PauseState::update(sf::Time dt) {

	return false;
}

void PauseState::draw() {

	sf::RenderWindow* window = getContext().window;

	int width = window->getSize().x;
	int height = window->getSize().y;

	window->setView(sf::View(sf::FloatRect(0.f, 0.f, width, height)));

	window->draw(m_bg);
	window->draw(m_title);

	for (auto& text : m_optionTexts)
		window->draw(text);

	window->draw(m_selectedLine);

}

void PauseState::updateSelected() {

	// Play select sound
	getContext().sounds->play(Sounds::Select);

	m_selectedLine.setSize(sf::Vector2f(m_optionTexts.at(m_selectedIndex).getLocalBounds().width, 4.0f));
	sf::FloatRect bounds = m_selectedLine.getLocalBounds();
	m_selectedLine.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	m_selectedLine.setPosition(m_optionTexts.at(m_selectedIndex).getPosition().x,
		m_optionTexts.at(m_selectedIndex).getPosition().y + m_optionTexts.at(m_selectedIndex).getGlobalBounds().height);

}

void PauseState::setPositions() {

	sf::RenderWindow* window = getContext().window;

	int width = window->getSize().x;
	int height = window->getSize().y;

	float halfWindowWidth = window->getSize().x / 2.0f;

	m_title.setPosition(halfWindowWidth, 150);
	Utils::centerTextOrigin(m_title);

	m_bg.setSize(sf::Vector2f(width, height));
	m_bg.setPosition(0.f, 0.f);

	// Update positions for options texts

	Utils::centerTextOrigin(m_optionTexts[Resume]);
	m_optionTexts[Resume].setPosition(halfWindowWidth, 300.f);

	Utils::centerTextOrigin(m_optionTexts[RestartLevel]);
	m_optionTexts[RestartLevel].setPosition(halfWindowWidth, 400.f);

	Utils::centerTextOrigin(m_optionTexts[Quit]);
	m_optionTexts[Quit].setPosition(halfWindowWidth, 500.f);


}