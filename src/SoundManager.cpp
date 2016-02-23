#include "SoundManager.h"

SoundManager::SoundManager()
{

	m_filenameMap.insert({ Sounds::ID::Shoot, "res/sounds/Shoot_02.ogg" });
	m_filenameMap.insert({ Sounds::ID::ShootFireball, "res/sounds/Shoot_01.ogg" });
	m_filenameMap.insert({ Sounds::ID::Jump, "res/sounds/Jump_00.ogg" });
	m_filenameMap.insert({ Sounds::ID::HitEnemy, "res/sounds/Hit_00.ogg" });
	m_filenameMap.insert({ Sounds::ID::HitPlayer, "res/sounds/Hit_01.ogg" });
	m_filenameMap.insert({ Sounds::ID::Pickup, "res/sounds/pickup.ogg" });
	m_filenameMap.insert({ Sounds::ID::Select, "res/sounds/Menu_Navigate_03.ogg" });

}

SoundManager::~SoundManager() {
}

const sf::SoundBuffer& SoundManager::get(Sounds::ID id) {

	auto sound = m_soundMap.find(id);

	if (sound == m_soundMap.end()) // Sound not yet loaded
		return load(id); // Load and return
	else // Sound already loaded
		return *sound->second; // Return loaded sound

}

const sf::SoundBuffer& SoundManager::load(Sounds::ID id) {

	std::unique_ptr<sf::SoundBuffer> sound(new sf::SoundBuffer());
	if (!sound->loadFromFile(m_filenameMap.find(id)->second))
		throw std::runtime_error("Failed to load sound: " + m_filenameMap.find(id)->second);

	// Insert and return sound reference
	m_soundMap.insert(std::make_pair(id, std::move(sound)));

	auto t = m_soundMap.find(id);
	return *t->second;
}
