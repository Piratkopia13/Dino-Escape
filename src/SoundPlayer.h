#pragma once

#include <list>

#include <SFML/Audio.hpp>
#include "SoundManager.h"
#include "Common.h"

class SoundPlayer {

public:
	SoundPlayer();

	void play(Sounds::ID soundID);
	void play(Sounds::ID soundID, sf::Vector2f position);

	void removeStoppedSounds();
	void setListenerPosition(sf::Vector2f position);
	sf::Vector2f getListenerPosition() const;

private:
	SoundManager m_soundManager;
	std::list<sf::Sound> m_sounds;

	const float m_listenerZ;
	const float m_attenuation;
	const float m_minDistance2D;
	const float m_minDistance3D;

};
