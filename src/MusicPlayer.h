#pragma once

#include <map>
#include <string>

#include <SFML/Audio.hpp>
#include "Common.h"

// Owns and handles playing of music resources
class MusicPlayer {

public:
	MusicPlayer();

	// Plays the music linked to the id
	void play(Music::ID theme);
	// Stops the music
	void stop();

	// Pauses/resumes the music
	void setPaused(const bool paused);
	// Sets the volume of the music
	void setVolume(const float volume);

private:
	// The music currently playing
	sf::Music m_music;
	// Music filenames on disk mapped by the Music::ID identifier
	std::map<Music::ID, std::string> m_filenames;
	// The current volume
	float m_volume;

};
