#pragma once

#include <map>
#include <memory>
#include <iostream>

#include "Common.h"

class TextureManager {

public:
	TextureManager();
	~TextureManager();

	const sf::Texture& get(Textures::ID id);

private:
	const sf::Texture& load(Textures::ID id);

private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> m_textureMap;
	std::map<Textures::ID, std::string> m_filenameMap;


};
