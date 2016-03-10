#pragma once

#include <map>
#include <string>
#include <memory>

#include "Common.h"
#include <SFML/Audio.hpp>

// Owns and distributes sound buffer resources
class SoundManager {

public:
	SoundManager();

	// Returns a sound buffer reference by id
	const sf::SoundBuffer& get(Sounds::ID id);

private:
	// Loads the sound buffer from the disk
	const sf::SoundBuffer& load(Sounds::ID id);

private:
	// sf::SoundBuffer mapped by the Sounds::ID identifier
	std::map<Sounds::ID, std::unique_ptr<sf::SoundBuffer>> m_soundMap;
	// Sound buffer filenames on disk mapped by the Sounds::ID identifier
	std::map<Sounds::ID, std::string> m_filenameMap;


};
