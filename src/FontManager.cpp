#include "FontManager.h"

FontManager::FontManager() {

	// TODO: Load filenames from a file or something
	m_filenameMap.insert({ Fonts::ID::Main, "res/fonts/emulogic.ttf" });
	m_filenameMap.insert({ Fonts::ID::Roboto, "res/fonts/Roboto-Regular.ttf" });

}

FontManager::~FontManager() {
}

const sf::Font& FontManager::get(Fonts::ID id) {

	auto font = m_fontMap.find(id);

	if (font == m_fontMap.end()) // Font not yet loaded
		return load(id); // Load and return
	else // Font already loaded
		return *font->second; // Return loaded font

}

const sf::Font& FontManager::load(Fonts::ID id) {

	std::unique_ptr<sf::Font> font(new sf::Font());
	if (!font->loadFromFile(m_filenameMap.find(id)->second))
		throw std::runtime_error("Failed to load font: " + m_filenameMap.find(id)->second);

	// Insert and return font reference
	m_fontMap.insert(std::make_pair(id, std::move(font)));

	auto t = m_fontMap.find(id);
	return *t->second;
}
