#include "SoundManager.h"

SoundManager::SoundManager() {

	// Map filenames to IDs
	m_filenameMap.insert({ Sounds::ID::Shoot, "res/sounds/Shoot_02.ogg" });
	m_filenameMap.insert({ Sounds::ID::ShootFireball, "res/sounds/Shoot_01.ogg" });
	m_filenameMap.insert({ Sounds::ID::Jump, "res/sounds/Jump_00.ogg" });
	m_filenameMap.insert({ Sounds::ID::HitEnemy, "res/sounds/Hit_00.ogg" });
	m_filenameMap.insert({ Sounds::ID::HitPlayer, "res/sounds/Hit_01.ogg" });
	m_filenameMap.insert({ Sounds::ID::Pickup, "res/sounds/pickup.ogg" });
	m_filenameMap.insert({ Sounds::ID::Select, "res/sounds/Menu_Navigate_03.ogg" });
	m_filenameMap.insert({ Sounds::ID::WinJingle, "res/sounds/Jingle_Win.ogg" });
	m_filenameMap.insert({ Sounds::ID::LoseJingle, "res/sounds/Jingle_Lose.ogg" });

}

const sf::SoundBuffer& SoundManager::get(Sounds::ID id) {

	auto sound = m_soundMap.find(id);

	// Check if the sound buffer has not yet been loaded
	if (sound == m_soundMap.end())
		// Load and return
		return load(id);
	else
		// Return loaded sound
		return *sound->second;

}

const sf::SoundBuffer& SoundManager::load(Sounds::ID id) {

	std::unique_ptr<sf::SoundBuffer> sound(new sf::SoundBuffer());

	// Check if the load faled
	if (!sound->loadFromFile(m_filenameMap.find(id)->second))
		throw std::logic_error("Failed to load sound: " + m_filenameMap.find(id)->second);

	// Insert and return sound buffer reference
	auto insertedPair = m_soundMap.insert(std::make_pair(id, std::move(sound)));
	return *insertedPair.first->second;
}
