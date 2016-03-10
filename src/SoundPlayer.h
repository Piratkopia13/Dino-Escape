#pragma once

#include <list>

#include <SFML/Audio.hpp>
#include "SoundManager.h"
#include "Common.h"

// Owns and handles playing of sound resources
class SoundPlayer {

public:
	SoundPlayer();

	// Plays the sound linked to the id
	void play(Sounds::ID soundID);
	// Plays the sound linked to the id spatialized
	void play(Sounds::ID soundID, sf::Vector2f position);

	// Removes all stopped sounds from memory
	// Should be called every frame or when needed
	void removeStoppedSounds();
	// Sets the position of the listener of spatialized sounds
	void setListenerPosition(sf::Vector2f position);
	// Returns the position of the listened of spatialized sounds
	sf::Vector2f getListenerPosition() const;

private:
	// SoundManager owns the sf::SoundBuffer instances
	SoundManager m_soundManager;

	// List of sounds that are currently played or has been played but not removed yet
	// The use of std::list is that it wont relocate existing sounds when adding new ones and thereby invalidating them mid-play, like the std::vector could.
	// Using the std::list also allows for efficient removal of random elements without changing the element order.
	std::list<sf::Sound> m_sounds;

	// Z-position of the listener, hardcoded to be "in front of the screen"
	const float m_listenerZ;

	// OpenAL settings
	const float m_attenuation;
	const float m_minDistance2D;
	const float m_minDistance3D;

};
