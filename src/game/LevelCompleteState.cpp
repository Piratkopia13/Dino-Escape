#include "LevelCompleteState.h"

LevelCompleteState::LevelCompleteState(StateStack& stack, Context context) 
: State(stack, context)
{

	const unsigned int currentLevel = context.levels->getCurrentLevelIndex();
	// Set the next level as current
	bool notLastLevel = context.levels->goToNextLevel();
	const unsigned int nextLevel = context.levels->getCurrentLevelIndex();


	sf::RenderWindow* window = getContext().window;

	m_bg.setSize(sf::Vector2f(window->getSize()));
	m_bg.setFillColor(sf::Color(16, 125, 166, 255));

	m_titleText.setFont(getContext().fonts->get(FontManager::Emulogic));
	m_titleText.setColor(sf::Color::Green);
	m_titleText.setCharacterSize(50);
	m_titleText.setString("Level " + std::to_string(currentLevel) + " complete!");
	Utils::centerTextOrigin(m_titleText);
	m_titleText.setPosition(window->getSize().x / 2.0f, 100.f);

	m_statsTitleText.setFont(getContext().fonts->get(FontManager::Emulogic));
	m_statsTitleText.setColor(sf::Color::White);
	m_statsTitleText.setCharacterSize(30);
	m_statsTitleText.setString("Stats");
	Utils::centerTextOrigin(m_statsTitleText);
	m_statsTitleText.setPosition(window->getSize().x / 2.0f, 300.f);

	// Stats 
	// Time
	// Health +6
	// Enemies killed +5
	// Total score = (maxTime - Time in seconds) * constant + health*10 + enemies killed*10

	m_statsText.setFont(getContext().fonts->get(FontManager::Emulogic));
	m_statsText.setColor(sf::Color::White);
	m_statsText.setCharacterSize(20);
	m_statsText.setString("Time: 1 min 23 sec");
	Utils::centerTextOrigin(m_statsText);
	m_statsText.setPosition(window->getSize().x / 2.0f, 350.f);

	m_continueText.setFont(getContext().fonts->get(FontManager::Emulogic));
	m_continueText.setColor(sf::Color::White);
	m_continueText.setCharacterSize(20);

	if (notLastLevel)
		m_continueText.setString("Press 'Enter' to start level " + std::to_string(nextLevel));
	else
		m_continueText.setString("No more levels, press 'Enter' to replay from level 1");

	Utils::centerTextOrigin(m_continueText);
	m_continueText.setPosition(window->getSize().x / 2.0f, window->getSize().y - 50.f);


}
LevelCompleteState::~LevelCompleteState() {
}

bool LevelCompleteState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::Return) {
			requestStackPop();
			requestStackPush(States::Game);
		}

	}

	return false;

}
bool LevelCompleteState::update(sf::Time dt) {
	return false;
}
void LevelCompleteState::draw() {
		
	sf::RenderWindow* window = getContext().window;

	window->draw(m_bg);
	window->draw(m_titleText);
	window->draw(m_statsTitleText);
	window->draw(m_statsText);
	window->draw(m_continueText);

}