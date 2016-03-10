#pragma once

#include <vector>
#include <string>
#include "Common.h"

// Keeps track of game levels and statistics
class LevelManager {

public:
	// Struct of all statistics data stored after a level is completed
	struct Stats {
		Stats(const sf::Time& finishTime = sf::seconds(0.f), unsigned int health = 0, unsigned int enemiesKilled = 0);
		sf::Time finishTime;
		unsigned int health;
		unsigned int enemiesKilled;
	};

public:
	LevelManager();
	
	// Returns false if there is no next level
	bool goToNextLevel();

	// Returns the filename of the current level
	const std::string& getCurrentLevelFile() const;
	// Returns the current level index
	const unsigned int getCurrentLevelIndex() const;
	
	// Returns the current statistics
	const Stats& getCurrentStats() const;
	// Updates the level statistics
	void setStats(const Stats& stats);

private:
	// List of filenames for all levels
	std::vector<std::string> m_levelFilenames;
	// Index of the current level
	unsigned int m_currentLevelIndex;

	// Current statistics
	Stats m_currentStats;
};