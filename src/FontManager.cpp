#include "FontManager.h"

FontManager::FontManager() {

	// Map filenames to IDs
	m_filenameMap.insert({ Fonts::ID::Main, "res/fonts/emulogic.ttf" });
	m_filenameMap.insert({ Fonts::ID::Roboto, "res/fonts/Roboto-Regular.ttf" });

}

const sf::Font& FontManager::get(Fonts::ID id) {

	auto font = m_fontMap.find(id);

	// Check if the font has not yet been loaded
	if (font == m_fontMap.end())
		// Load and return
		return load(id);
	else
		// Return loaded font
		return *font->second;

}

const sf::Font& FontManager::load(Fonts::ID id) {

	std::unique_ptr<sf::Font> font(new sf::Font());

	// Check if the load failed
	if (!font->loadFromFile(m_filenameMap.find(id)->second))
		throw std::logic_error("Failed to load font: " + m_filenameMap.find(id)->second);

	// Insert and return font reference
	auto insertedPair = m_fontMap.insert(std::make_pair(id, std::move(font)));
	return *insertedPair.first->second;
}
