#pragma once

// You may enable/disable the following defines

//#define ENABLE_DEBUG_SHAPES
//#define ENABLE_DEBUG_RAYS


// You may NOT modify anything below

// Define handy macros for usage of the debug renderer
#ifdef ENABLE_DEBUG_SHAPES

#define DRAW_DEBUG_IF_ENABLED(x) DebugRenderer::draw(x)
#define ADD_DEBUG_SHAPE_IF_ENABLED(bounds, color) DebugRenderer::addShape(bounds, color)

#else

#define DRAW_DEBUG_IF_ENABLED(x) 
#define ADD_DEBUG_SHAPE_IF_ENABLED(bounds, color)

#endif

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include "ResourceIdentifiers.h"
#include "Utils.h"

// Forward declaration of the classes that the context needs
class TextureManager;
class FontManager;
class LevelManager;
class MusicPlayer;
class SoundPlayer;
class PostEffectManager;

// The context contains pointers to data that all states in the game should be able to access
struct Context {
	Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts, LevelManager& levels, MusicPlayer& music, SoundPlayer& sounds, PostEffectManager& shaders);

	std::string versionText = "Beta release build 0.9";

	sf::RenderWindow* window;
	TextureManager* textures;
	FontManager* fonts;
	LevelManager* levels;
	MusicPlayer* music;
	SoundPlayer* sounds;
	PostEffectManager* shaders;
};