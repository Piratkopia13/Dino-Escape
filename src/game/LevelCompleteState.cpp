#include "LevelCompleteState.h"

LevelCompleteState::LevelCompleteState(StateStack& stack, Context& context) 
: State(stack, context)
{

	// Store the current level
	const unsigned int currentLevel = getContext().levels->getCurrentLevelIndex();
	// Set the next level as current, keep track of if this was the last level or not
	bool notLastLevel = getContext().levels->goToNextLevel();
	// Get the index of the next level
	const unsigned int nextLevel = getContext().levels->getCurrentLevelIndex();

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Set the color of the background
	m_bg.setFillColor(sf::Color(16, 125, 166, 255));

	// Set up the title
	Utils::createCenteredText(m_titleText, sf::Color::Green, 50,
		"Level " + std::to_string(currentLevel) + " complete!", getContext());

	// Set up the stats title
	Utils::createCenteredText(m_statsTitleText, sf::Color::White, 30,
		"Stats", getContext());

	// Get the current stats
	auto& stats = getContext().levels->getCurrentStats();

	// Calculate score
	int totalScore = static_cast<int>((300 - stats.finishTime.asSeconds()) * 0.3f);
	totalScore += stats.health * 10;
	totalScore += stats.enemiesKilled * 10;

	// Convert the time stat to a string
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << stats.finishTime.asSeconds();
	std::string time = stream.str();

	// Set up stat titles with there corresponding stat
	
	Utils::createText(m_statsTimeTitleText, sf::Color::White, 20, "Time:", getContext());
	Utils::createText(m_statsTimeText, sf::Color::White, 20, time + " sec", getContext());

	Utils::createText(m_statsHealthTitleText, sf::Color::White, 20, "Remaining health:", getContext());
	Utils::createText(m_statsHealthText, sf::Color::White, 20, std::to_string(stats.health), getContext());

	Utils::createText(m_statsKilledTitleText, sf::Color::White, 20, "Enemies killed:", getContext());
	Utils::createText(m_statsKilledText, sf::Color::White, 20, std::to_string(stats.enemiesKilled), getContext());

	// Set up total score text
	Utils::createCenteredText(m_statsScoreText, sf::Color::Yellow, 25, "Total score: " + std::to_string(totalScore), getContext());

	// Set up continue text
	Utils::createText(m_continueText, sf::Color::White, 20, "", getContext());

	// Set the continue text depending on if the last level was finished or not
	if (notLastLevel)
		m_continueText.setString("Press 'Enter' to start level " + std::to_string(nextLevel));
	else
		m_continueText.setString("No more levels, press 'Enter' to replay from level 1");

	// Center the text after content was modified
	Utils::centerTextOrigin(m_continueText);

	// Set the positions of all elements
	setPositions();


	// Stop music
	getContext().music->stop();
	// Play win jingle
	getContext().sounds->play(Sounds::WinJingle);

}

void LevelCompleteState::setPositions() {

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Get the window size
	int width = window->getSize().x;
	int height = window->getSize().y;

	// Update the window view to look good when the window resizes
	window->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))));

	// Store half the window's width
	float halfWindowWidth = window->getSize().x / 2.0f;

	// Set the backgruond size to fill the window
	m_bg.setSize(sf::Vector2f(window->getSize()));

	// Place the titles horizontally centered with different y positions
	m_titleText.setPosition(halfWindowWidth, 100.f);
	m_statsTitleText.setPosition(halfWindowWidth, 250.f);
	m_statsScoreText.setPosition(halfWindowWidth, 500.f);
	
	// Place the stat titles a bit to the left of the center with different y positions
	m_statsTimeTitleText.setPosition(halfWindowWidth - 300.f, 330.f);
	m_statsHealthTitleText.setPosition(halfWindowWidth - 300.f, 380.f);
	m_statsKilledTitleText.setPosition(halfWindowWidth - 300.f, 430.f);

	// Place the stats a bit to the right of the center with different y positions
	m_statsTimeText.setPosition(halfWindowWidth + 100.f, 330.f);
	m_statsHealthText.setPosition(halfWindowWidth + 100.f, 380.f);
	m_statsKilledText.setPosition(halfWindowWidth + 100.f, 430.f);

	// Set the continue text at almost the bottom and horizontally centered
	m_continueText.setPosition(halfWindowWidth, window->getSize().y - 50.f);

}

bool LevelCompleteState::handleEvent(const sf::Event& event) {

	// Check if a key was pressed
	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::Return) {
			// Enter key bound to start the next level

			// Pop this state
			requestStackPop();
			// Push a new game state, which will load with the next level
			requestStackPush(States::Game);
		}

	} else if (event.type == sf::Event::Resized) {

		// Update text positions
		setPositions();

	}

	// Don't allow underlying states to handle events
	return false;

}
bool LevelCompleteState::update(sf::Time dt) {

	// Don't allow underlying states update
	return false;

}
void LevelCompleteState::draw() {
		
	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Render elements
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