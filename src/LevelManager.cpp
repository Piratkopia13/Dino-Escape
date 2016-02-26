#include "LevelManager.h"

LevelManager::LevelManager()
: m_currentLevelIndex(0)
, m_currentStats(sf::seconds(0.f), 0, 0)
{
	
	// TODO: read this from a file
	m_levelFilenames.push_back("level1.json");
	m_levelFilenames.push_back("level2.json");

}
LevelManager::~LevelManager() {
}

bool LevelManager::goToNextLevel() {

	// Check if the last level has already been completed
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
LevelManager::Stats LevelManager::getCurrentStats() const {
	return m_currentStats;
}
