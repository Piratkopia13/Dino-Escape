#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
	: m_soundManager()
{

}

void SoundPlayer::play(Sounds::ID sound) {
	m_sounds.push_back(sf::Sound(m_soundManager.get(sound)));
	m_sounds.back().play();
}
void SoundPlayer::play(Sounds::ID sound, sf::Vector2f position) {

}

void SoundPlayer::removeStoppedSounds() {

	m_sounds.remove_if([](const sf::Sound& s) {
		return s.getStatus() == sf::Sound::Stopped;
	});

}
void SoundPlayer::setListenerPosition(sf::Vector2f position) {

}
sf::Vector2f SoundPlayer::getListenerPosition() const {
	return sf::Vector2f(0, 0);
}