#include "LevelCompleteState.h"

LevelCompleteState::LevelCompleteState(StateStack& stack, Context& context) 
: State(stack, context)
{

	const unsigned int currentLevel = context.levels->getCurrentLevelIndex();
	// Set the next level as current
	bool notLastLevel = context.levels->goToNextLevel();
	const unsigned int nextLevel = context.levels->getCurrentLevelIndex();


	sf::RenderWindow* window = getContext().window;

	m_bg.setFillColor(sf::Color(16, 125, 166, 255));

	m_titleText.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_titleText.setColor(sf::Color::Green);
	m_titleText.setCharacterSize(50);
	m_titleText.setString("Level " + std::to_string(currentLevel) + " complete!");
	Utils::centerTextOrigin(m_titleText);

	m_statsTitleText.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_statsTitleText.setColor(sf::Color::White);
	m_statsTitleText.setCharacterSize(30);
	m_statsTitleText.setString("Stats");
	Utils::centerTextOrigin(m_statsTitleText);

	// Stats 
	// Time
	// Health +6
	// Enemies killed +5
	// Total score = (maxTime - Time in seconds) * constant + health*10 + enemies killed*10

	m_statsText.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_statsText.setColor(sf::Color::White);
	m_statsText.setCharacterSize(20);
	m_statsText.setString("Time: 1 min 23 sec");
	Utils::centerTextOrigin(m_statsText);

	m_continueText.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_continueText.setColor(sf::Color::White);
	m_continueText.setCharacterSize(20);

	if (notLastLevel)
		m_continueText.setString("Press 'Enter' to start level " + std::to_string(nextLevel));
	else
		m_continueText.setString("No more levels, press 'Enter' to replay from level 1");

	Utils::centerTextOrigin(m_continueText);

	setPositions();

}
LevelCompleteState::~LevelCompleteState() {
}

void LevelCompleteState::setPositions() {

	sf::RenderWindow* window = getContext().window;

	int width = window->getSize().x;
	int height = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0, 0, width, height)));

	float halfWindowWidth = window->getSize().x / 2.0f;

	m_bg.setSize(sf::Vector2f(window->getSize()));

	m_titleText.setPosition(halfWindowWidth, 100.f);
	m_statsTitleText.setPosition(halfWindowWidth, 300.f);
	m_statsText.setPosition(halfWindowWidth, 350.f);
	m_continueText.setPosition(halfWindowWidth, window->getSize().y - 50.f);

}

bool LevelCompleteState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::Return) {
			requestStackPop();
			requestStackPush(States::Game);
		}

	} else if (event.type == sf::Event::Resized) {

		// Update text positions
		setPositions();

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