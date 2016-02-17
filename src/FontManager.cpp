#include "FontManager.h"

FontManager::FontManager() {

	// TODO: Load filenames from a file or something
	m_filenameMap.insert({ FontID::Roboto, "res/fonts/Roboto-Regular.ttf" });
	m_filenameMap.insert({ FontID::Emulogic, "res/fonts/emulogic.ttf" });

}

FontManager::~FontManager() {

	for (auto& p : m_fontMap) {
		if (p.second.get() == nullptr)
			std::cout << "Nullptr at FontID: " << p.first << std::endl;
	}


}

const sf::Font& FontManager::get(const FontID& id) {

	std::cout << "Got font for id " << id << std::endl;

	auto tex = m_fontMap.find(id);

	if (tex == m_fontMap.end()) // Font not yet loaded
		return load(id); // Load and return
	else // Font already loaded
		return *tex->second; // Return loaded font

}

const sf::Font& FontManager::load(const FontID& id) {

	std::cout << "Loaded font for id " << id << std::endl;

	std::unique_ptr<sf::Font> font(new sf::Font());
	font->loadFromFile(m_filenameMap.find(id)->second);

	// Insert and return font reference
	m_fontMap.insert(std::make_pair(id, std::move(font)));

	auto t = m_fontMap.find(id);
	return *t->second;
}
