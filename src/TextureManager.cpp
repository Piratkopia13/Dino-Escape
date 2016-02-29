#include "TextureManager.h"

TextureManager::TextureManager() {

	m_filenameMap.insert({ Textures::ID::Dino, "res/textures/dino.png" });
	m_filenameMap.insert({ Textures::ID::Enemies, "res/textures/enemies.png" });
	m_filenameMap.insert({ Textures::ID::Items, "res/textures/items.png" });
	m_filenameMap.insert({ Textures::ID::MenuBackground, "res/textures/menu_background.png" });
	m_filenameMap.insert({ Textures::ID::HealthBar, "res/textures/meter.png" });
	m_filenameMap.insert({ Textures::ID::Default, "res/textures/default.png" });

}

TextureManager::~TextureManager() {
}

const sf::Texture& TextureManager::get(Textures::ID id) {

	int siz = m_textureMap.size();

	auto tex = m_textureMap.find(id);

	if (tex == m_textureMap.end()) // Texture not yet loaded
		return load(id); // Load and return
	else // Texture already loaded
		return *tex->second; // Return loaded texture

}

const sf::Texture& TextureManager::load(Textures::ID id) {

	std::unique_ptr<sf::Texture> tex(new sf::Texture());
	
	if (!tex->loadFromFile(m_filenameMap.find(id)->second))
		throw std::runtime_error("Failed to load texture: " + m_filenameMap.find(id)->second);

	// Insert and return texture reference
	m_textureMap.insert(std::make_pair(id, std::move(tex)));

	auto t = m_textureMap.find(id);
	return *t->second;
}
