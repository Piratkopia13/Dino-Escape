#include "TextureManager.h"

TextureManager::TextureManager() {

	// TODO: Load filenames from a file or something
	m_filenameMap.insert({ Textures::ID::DINO, "res/textures/dino.png" });
	m_filenameMap.insert({ Textures::ID::ENEMIES, "res/textures/enemies.png" });
	m_filenameMap.insert({ Textures::ID::ITEMS, "res/textures/items.png" });
	m_filenameMap.insert({ Textures::ID::MENU_BACKGROUND, "res/textures/menu_background.png" });
	m_filenameMap.insert({ Textures::ID::HEALTH_BAR, "res/textures/meter.png" });

}

TextureManager::~TextureManager() {
}

const sf::Texture& TextureManager::get(Textures::ID id) {

	int siz = m_textureMap.size();

	std::cout << "Got texture for id " << id << std::endl;

	auto tex = m_textureMap.find(id);

	if (tex == m_textureMap.end()) // Texture not yet loaded
		return load(id); // Load and return
	else // Texture already loaded
		return *tex->second; // Return loaded texture

}

const sf::Texture& TextureManager::load(Textures::ID id) {

	std::cout << "Loaded texture for id " << id << std::endl;

	std::unique_ptr<sf::Texture> tex(new sf::Texture());
	tex->loadFromFile(m_filenameMap.find(id)->second);

	// Insert and return texture reference
	m_textureMap.insert(std::make_pair(id, std::move(tex)));

	auto t = m_textureMap.find(id);
	return *t->second;
}
