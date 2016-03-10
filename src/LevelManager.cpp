#include "LevelManager.h"

LevelManager::LevelManager()
: m_currentLevelIndex(0)
, m_currentStats(sf::seconds(0.f), 0, 0)
{
	
	// Load map order from file
	std::string levelOrderData = Utils::readFile("res/maps/level.order");
	// Store individual lines in m_levelFilenames
	Utils::splitString(levelOrderData, '\n', m_levelFilenames);

}

bool LevelManager::goToNextLevel() {

	// Check if the current level was the last one
	if (m_currentLevelIndex == m_levelFilenames.size() - 1) {

		// Set the first level as current
		m_currentLevelIndex = 0;

		return false;
	}

	// Increase level index
	m_currentLevelIndex++;

	return true;
}

const std::string& LevelManager::getCurrentLevelFile() const {
	return m_levelFilenames.at(m_currentLevelIndex);
}

const unsigned int LevelManager::getCurrentLevelIndex() const {
	return m_currentLevelIndex + 1;
}


LevelManager::Stats::Stats(const sf::Time& finishTime, unsigned int health, unsigned int enemiesKilled)
	: finishTime(finishTime)
	, health(health)
	, enemiesKilled(enemiesKilled) {

}

void LevelManager::setStats(const Stats& stats) {
	m_currentStats = stats;
}
const LevelManager::Stats& LevelManager::getCurrentStats() const {
	return m_currentStats;
}
