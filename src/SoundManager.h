#pragma once

#include <map>
#include <string>
#include <memory>
#include <iostream>

#include "Common.h"
#include <SFML\Audio\SoundBuffer.hpp>

class SoundManager {

public:
	SoundManager();
	~SoundManager();

	const sf::SoundBuffer& get(Sounds::ID id);

private:
	const sf::SoundBuffer& load(Sounds::ID id);

private:
	std::map<Sounds::ID, std::unique_ptr<sf::SoundBuffer>> m_soundMap;
	std::map<Sounds::ID, std::string> m_filenameMap;


};
