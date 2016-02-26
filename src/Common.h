#pragma once

//#define ENABLE_DEBUG_SHAPES
//#define ENABLE_DEBUG_RAYS

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include "ResourceIdentifiers.h"
#include "Utils.h"

class TextureManager;
class FontManager;
class LevelManager;
class MusicPlayer;
class SoundPlayer;

struct Context {
	Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts, LevelManager& levels, MusicPlayer& music, SoundPlayer& sounds);

	sf::RenderWindow* window;
	TextureManager* textures;
	FontManager* fonts;
	LevelManager* levels;
	MusicPlayer* music;
	SoundPlayer* sounds;
};