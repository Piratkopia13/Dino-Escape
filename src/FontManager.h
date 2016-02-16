#pragma once

#include <map>
#include <memory>
#include <iostream>

#include "Common.h"

class FontManager {

public:
	enum FontID {
		Roboto
	};

public:
	FontManager();
	~FontManager();

	const sf::Font& get(const FontID& id);

private:
	const sf::Font& load(const FontID& id);

private:
	std::map<FontID, std::unique_ptr<sf::Font>> m_fontMap;
	std::map<FontID, std::string> m_filenameMap;


};
