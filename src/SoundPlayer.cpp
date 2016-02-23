#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
: m_soundManager()
, m_listenerZ(300.f)
, m_attenuation(8.f)
, m_minDistance2D(200.f)
, m_minDistance3D(std::sqrt(m_minDistance2D*m_minDistance2D + m_listenerZ*m_listenerZ))
{

}

void SoundPlayer::play(Sounds::ID soundID) {
	play(soundID, getListenerPosition());
}

void SoundPlayer::play(Sounds::ID soundID, sf::Vector2f position) {

	m_sounds.push_back(sf::Sound(m_soundManager.get(soundID)));
	sf::Sound& sound = m_sounds.back();

	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(m_attenuation);
	sound.setMinDistance(m_minDistance3D);

	sound.play();

}

void SoundPlayer::removeStoppedSounds() {

	m_sounds.remove_if([](const sf::Sound& s) {
		return s.getStatus() == sf::Sound::Stopped;
	});

}
void SoundPlayer::setListenerPosition(sf::Vector2f position) {
	sf::Listener::setPosition(position.x, -position.y, m_listenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const {
	sf::Vector3f globalPos = sf::Listener::getPosition();
	return sf::Vector2f(globalPos.x, -globalPos.y);
}