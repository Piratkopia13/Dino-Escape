#include "LevelManager.h"

LevelManager::LevelManager()
: m_currentLevelIndex(0)
{
	
	// TODO: read this from a file
	m_levelFileNames.push_back("level1.json");
	m_levelFileNames.push_back("level2.json");

}
LevelManager::~LevelManager() {
}

bool LevelManager::goToNextLevel() {

	// Check if the last level has already been completed
	if (m_currentLevelIndex == m_levelFileNames.size() - 1) {

		// Set the first level as current
		m_currentLevelIndex = 0;

		return false;
	}

	// Increase level index
	m_currentLevelIndex++;

	return true;
}

const std::string& LevelManager::getCurrentLevelFile() const {
	return m_levelFileNames.at(m_currentLevelIndex);
}

const unsigned int& LevelManager::getCurrentLevelIndex() const {
	return m_currentLevelIndex + 1;
}
