#pragma once

#include <map>
#include <memory>
#include <iostream>

#include "Common.h"

class FontManager {

public:
	FontManager();
	~FontManager();

	const sf::Font& get(Fonts::ID id);

private:
	const sf::Font& load(Fonts::ID id);

private:
	std::map<Fonts::ID, std::unique_ptr<sf::Font>> m_fontMap;
	std::map<Fonts::ID, std::string> m_filenameMap;


};
