#pragma once

#include <vector>
#include <string>

class LevelManager {

public:
	LevelManager();
	~LevelManager();
	
	// Returns false if there is no next level
	bool goToNextLevel();
	const std::string& getCurrentLevelFile() const;
	const unsigned int getCurrentLevelIndex() const;

private:
	std::vector<std::string> m_levelFilenames;
	unsigned int m_currentLevelIndex;

};