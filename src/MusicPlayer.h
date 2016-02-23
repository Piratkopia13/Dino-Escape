#pragma once

#include <map>
#include <string>

#include <SFML\Audio\Music.hpp>
#include "Common.h"

class MusicPlayer {

public:
	MusicPlayer();

	void play(Music::ID theme);
	void stop();

	void setPaused(const bool paused);
	void setVolume(const float volume);

private:
	sf::Music m_music;
	std::map<Music::ID, std::string> m_filenames;
	float m_volume;

};
