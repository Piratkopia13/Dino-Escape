#pragma once

#include <list>

#include <SFML\Audio\Sound.hpp>
#include "SoundManager.h"
#include "Common.h"

class SoundPlayer {

public:
	SoundPlayer();

	void play(Sounds::ID sound);
	void play(Sounds::ID sound, sf::Vector2f position);

	void removeStoppedSounds();
	void setListenerPosition(sf::Vector2f position);
	sf::Vector2f getListenerPosition() const;

private:
	SoundManager m_soundManager;
	std::list<sf::Sound> m_sounds;

};
