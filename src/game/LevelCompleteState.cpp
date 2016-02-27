#include "LevelCompleteState.h"

LevelCompleteState::LevelCompleteState(StateStack& stack, Context& context) 
: State(stack, context)
, m_stats(getContext().levels->getCurrentStats())
{

	const unsigned int currentLevel = context.levels->getCurrentLevelIndex();
	// Set the next level as current
	bool notLastLevel = context.levels->goToNextLevel();
	const unsigned int nextLevel = context.levels->getCurrentLevelIndex();


	sf::RenderWindow* window = getContext().window;

	m_bg.setFillColor(sf::Color(16, 125, 166, 255));

	Utils::createCenteredText(m_titleText, sf::Color::Green, 50,
		"Level " + std::to_string(currentLevel) + " complete!", getContext());

	Utils::createCenteredText(m_statsTitleText, sf::Color::White, 30,
		"Stats", getContext());

	// Calculate score
	int totalScore = (300 - m_stats.finishTime.asSeconds()) * 0.3f;
	totalScore += m_stats.health * 10;
	totalScore += m_stats.enemiesKilled * 10;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << m_stats.finishTime.asSeconds();
	std::string time = stream.str();

	Utils::createText(m_statsTimeTitleText, sf::Color::White, 20, "Time:", getContext());
	Utils::createText(m_statsTimeText, sf::Color::White, 20, time + " sec", getContext());

	Utils::createText(m_statsHealthTitleText, sf::Color::White, 20, "Remaining health:", getContext());
	Utils::createText(m_statsHealthText, sf::Color::White, 20, std::to_string(m_stats.health), getContext());

	Utils::createText(m_statsKilledTitleText, sf::Color::White, 20, "Enemies killed:", getContext());
	Utils::createText(m_statsKilledText, sf::Color::White, 20, std::to_string(m_stats.enemiesKilled), getContext());

	Utils::createCenteredText(m_statsScoreText, sf::Color::Yellow, 25, "Total score: " + std::to_string(totalScore), getContext());

	Utils::createCenteredText(m_continueText, sf::Color::White, 20, "", getContext());

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
	m_statsTitleText.setPosition(halfWindowWidth, 250.f);
	m_statsScoreText.setPosition(halfWindowWidth, 500.f);
	

	m_statsTimeTitleText.setPosition(halfWindowWidth - 300.f, 330.f);
	m_statsHealthTitleText.setPosition(halfWindowWidth - 300.f, 380.f);
	m_statsKilledTitleText.setPosition(halfWindowWidth - 300.f, 430.f);

	m_statsTimeText.setPosition(halfWindowWidth + 100.f, 330.f);
	m_statsHealthText.setPosition(halfWindowWidth + 100.f, 380.f);
	m_statsKilledText.setPosition(halfWindowWidth + 100.f, 430.f);

	
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

	window->draw(m_statsScoreText);

	window->draw(m_statsTimeTitleText);
	window->draw(m_statsHealthTitleText);
	window->draw(m_statsKilledTitleText);

	window->draw(m_statsTimeText);
	window->draw(m_statsHealthText);
	window->draw(m_statsKilledText);
	
	window->draw(m_continueText);

}