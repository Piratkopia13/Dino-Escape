#pragma once

#include <vector>
#include <string>
#include "Common.h"

class LevelManager {

public:
	struct Stats {
		Stats(const sf::Time& finishTime = sf::seconds(0.f), unsigned int health = 0, unsigned int enemiesKilled = 0);
		sf::Time finishTime;
		unsigned int health;
		unsigned int enemiesKilled;
	};

public:
	LevelManager();
	~LevelManager();
	
	// Returns false if there is no next level
	bool goToNextLevel();

	const std::string& getCurrentLevelFile() const;
	const unsigned int getCurrentLevelIndex() const;
	
	void setStats(const Stats& stats);
	Stats getCurrentStats() const;

private:
	std::vector<std::string> m_levelFilenames;
	unsigned int m_currentLevelIndex;

	Stats m_currentStats;
};