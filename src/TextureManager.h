#pragma once

#include <map>
#include <memory>

#include "Common.h"

// Owns and distributes texture resources
class TextureManager {

public:
	TextureManager();

	// Returns a texture reference by id
	const sf::Texture& get(Textures::ID id);

private:
	// Loads the texture from the disk
	const sf::Texture& load(Textures::ID id);

private:
	// sf::Texture mapped by the Textures::ID identifier
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> m_textureMap;
	// Texture filenames on disk mapped by the Textures::ID identifier
	std::map<Textures::ID, std::string> m_filenameMap;


};
