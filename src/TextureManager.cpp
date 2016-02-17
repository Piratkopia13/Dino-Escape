#include "TextureManager.h"

TextureManager::TextureManager() {

	// TODO: Load filenames from a file or something
	m_filenameMap.insert({ TextureID::DINO, "res/textures/dino.png" });
	m_filenameMap.insert({ TextureID::ENEMIES, "res/textures/enemies.png" });
	m_filenameMap.insert({ TextureID::ITEMS, "res/textures/items.png" });
	m_filenameMap.insert({ TextureID::MENU_BACKGROUND, "res/textures/menu_background.png" });

}

TextureManager::~TextureManager() {

	for (auto& p : m_textureMap) {
		if (p.second.get() == nullptr)
			std::cout << "Nullptr at textureID: " << p.first << std::endl;
	}


}

const sf::Texture& TextureManager::get(const TextureID& id) {
	
	std::cout << "Got texture for id " << id << std::endl;

	auto tex = m_textureMap.find(id);

	if (tex == m_textureMap.end()) // Texture not yet loaded
		return load(id); // Load and return
	else // Texture already loaded
		return *tex->second; // Return loaded texture

}

const sf::Texture& TextureManager::load(const TextureID& id) {

	std::cout << "Loaded texture for id " << id << std::endl;

	std::unique_ptr<sf::Texture> tex(new sf::Texture());
	tex->loadFromFile(m_filenameMap.find(id)->second);

	// Insert and return texture reference
	m_textureMap.insert(std::make_pair(id, std::move(tex)));

	auto t = m_textureMap.find(id);
	return *t->second;
}
