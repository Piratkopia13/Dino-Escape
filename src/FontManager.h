#pragma once

#include <map>
#include <memory>

#include "Common.h"

// Owns and distributes font resources
class FontManager {

public:
	FontManager();

	// Returns a font reference by id
	const sf::Font& get(Fonts::ID id);

private:
	// Loads the font from the disk
	const sf::Font& load(Fonts::ID id);

private:
	// sf::Font mapped by the Fonts::ID identifier
	std::map<Fonts::ID, std::unique_ptr<sf::Font>> m_fontMap;
	// Font filenames on disk mapped by the Fonts::ID identifier
	std::map<Fonts::ID, std::string> m_filenameMap;


};
