#pragma once

#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <iterator>

#include <cstdlib>

#include <SFML\Graphics.hpp>

struct Context;

// Contains various static utility methods
class Utils {

public:

	// Reads a file into a std::string
	static std::string readFile(const char* filepath);
	static void splitString(const std::string& str, char delim, std::vector<std::string>& output);

	static float linearInterpolation(float from, float to, float step);
	static sf::Vector2f linearInterpolation(const sf::Vector2f& from, const sf::Vector2f& to, float step);

	static sf::Vector2f normalize(sf::Vector2f& vec);

	static std::string vecToString(const sf::Vector2f& vec);

	static void centerTextOrigin(sf::Text& text);

	static void createCenteredText(sf::Text& theText, const sf::Color& color, unsigned int charSize, const std::string& content, const Context& context);
	static void createText(sf::Text& theText, const sf::Color& color, unsigned int charSize, const std::string& content, const Context& context);

	static float random(float min, float max);

};