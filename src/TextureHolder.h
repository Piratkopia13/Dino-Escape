#pragma once

#include <map>
#include <memory>
#include <iostream>

#include "Common.h"

class TextureHolder {

public:
	enum TextureID {
		DINO,
		ENEMIES,
		ITEMS
	};

public:
	TextureHolder();
	~TextureHolder();

	const sf::Texture& get(const TextureID& id);

private:
	const sf::Texture& load(const TextureID& id);

private:
	std::map<TextureID, std::unique_ptr<sf::Texture>> m_textureMap;
	std::map<TextureID, std::string> m_filenameMap;


};
