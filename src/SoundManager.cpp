#include "SoundManager.h"

SoundManager::SoundManager()
{

	m_filenameMap.insert({ Sounds::ID::Shoot, "res/sounds/laser.ogg" });
	m_filenameMap.insert({ Sounds::ID::Jump, "res/sounds/jump.ogg" });

}

SoundManager::~SoundManager() {
}

const sf::SoundBuffer& SoundManager::get(Sounds::ID id) {

	std::cout << "Got sound for id " << id << std::endl;

	auto sound = m_soundMap.find(id);

	if (sound == m_soundMap.end()) // Sound not yet loaded
		return load(id); // Load and return
	else // Sound already loaded
		return *sound->second; // Return loaded sound

}

const sf::SoundBuffer& SoundManager::load(Sounds::ID id) {

	std::cout << "Loaded sound for id " << id << std::endl;

	std::unique_ptr<sf::SoundBuffer> sound(new sf::SoundBuffer());
	if (!sound->loadFromFile(m_filenameMap.find(id)->second))
		throw std::runtime_error("Failed to load sound: " + m_filenameMap.find(id)->second);

	// Insert and return sound reference
	m_soundMap.insert(std::make_pair(id, std::move(sound)));

	auto t = m_soundMap.find(id);
	return *t->second;
}
