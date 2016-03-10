#include "TextureManager.h"

TextureManager::TextureManager() {

	// Map filenames to IDs
	m_filenameMap.insert({ Textures::ID::Dino, "res/textures/dino.png" });
	m_filenameMap.insert({ Textures::ID::Enemies, "res/textures/enemies.png" });
	m_filenameMap.insert({ Textures::ID::Items, "res/textures/items.png" });
	m_filenameMap.insert({ Textures::ID::MenuBackground, "res/textures/menu_background.png" });
	m_filenameMap.insert({ Textures::ID::ControlsBackground, "res/textures/controls_background.png" });
	m_filenameMap.insert({ Textures::ID::HealthBar, "res/textures/meter.png" });
	m_filenameMap.insert({ Textures::ID::Default, "res/textures/default.png" });

}

const sf::Texture& TextureManager::get(Textures::ID id) {

	auto tex = m_textureMap.find(id);

	// Check if the texture has not yet been loaded
	if (tex == m_textureMap.end())
		// Load and return
		return load(id);
	else
		// Return loaded texture
		return *tex->second;

}

const sf::Texture& TextureManager::load(Textures::ID id) {

	std::unique_ptr<sf::Texture> tex(new sf::Texture());
	
	// Check if the load failed
	if (!tex->loadFromFile(m_filenameMap.find(id)->second))
		throw std::logic_error("Failed to load texture: " + m_filenameMap.find(id)->second);

	// Insert and return texture reference
	auto insertedPair = m_textureMap.insert(std::make_pair(id, std::move(tex)));
	return *insertedPair.first->second;
}
