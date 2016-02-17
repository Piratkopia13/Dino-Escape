#pragma once

#include <map>
#include <memory>
#include <iostream>

#include "Common.h"

class TextureManager {

public:
	enum TextureID {
		DINO,
		ENEMIES,
		ITEMS,
		HEALTH_BAR,
		MENU_BACKGROUND
	};

public:
	TextureManager();
	~TextureManager();

	const sf::Texture& get(const TextureID& id);

private:
	const sf::Texture& load(const TextureID& id);

private:
	std::map<TextureID, std::unique_ptr<sf::Texture>> m_textureMap;
	std::map<TextureID, std::string> m_filenameMap;


};
