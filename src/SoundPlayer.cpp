#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
: m_soundManager()
, m_listenerZ(300.f)
, m_attenuation(3.f)
, m_minDistance2D(200.f)
, m_minDistance3D(std::sqrt(m_minDistance2D*m_minDistance2D + m_listenerZ*m_listenerZ))
{

}

void SoundPlayer::play(Sounds::ID soundID) {
	// Plays the sound from the listeners position, thereby despatializing it
	play(soundID, getListenerPosition());
}

void SoundPlayer::play(Sounds::ID soundID, sf::Vector2f position) {

	// Load the sound from the sf::SoundBuffer gotten from the SoundManager
	m_sounds.push_back(sf::Sound(m_soundManager.get(soundID)));
	// Get a reference to the sound
	sf::Sound& sound = m_sounds.back();

	// Set it up
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(m_attenuation);
	sound.setMinDistance(m_minDistance3D);

	// Play it
	sound.play();

}

void SoundPlayer::removeStoppedSounds() {

	// Makes use of lambda expressions to remove all sounds with the stopped status
	m_sounds.remove_if([](const sf::Sound& s) {
		return s.getStatus() == sf::Sound::Stopped;
	});

}
void SoundPlayer::setListenerPosition(sf::Vector2f position) {
	// SFML/OpenAL things
	sf::Listener::setPosition(position.x, -position.y, m_listenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const {
	// SFML/OpenAL things
	sf::Vector3f globalPos = sf::Listener::getPosition();
	return sf::Vector2f(globalPos.x, -globalPos.y);
}