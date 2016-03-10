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
	// Splits a string by a chosen delimiter, puts the result in the output parameter
	static void splitString(const std::string& str, char delim, std::vector<std::string>& output);

	// Linearly interpolates a float
	static float linearInterpolation(float from, float to, float step);
	// Linearly interpolates a sf::Vector2f
	static sf::Vector2f linearInterpolation(const sf::Vector2f& from, const sf::Vector2f& to, float step);

	// Normalizes a sf::Vector2f
	static sf::Vector2f normalize(sf::Vector2f& vec);

	// Converts a sf::Vector2f to a string 
	static std::string vecToString(const sf::Vector2f& vec);

	// Centers the origin of the sf::Text
	static void centerTextOrigin(sf::Text& text);

	// Sets up a sf::Text with the default game font and chosen parameters with centered origin
	static void createCenteredText(sf::Text& theText, const sf::Color& color, unsigned int charSize, const std::string& content, const Context& context);
	// Sets up a sf::Text with the default game font and chosen parameters
	static void createText(sf::Text& theText, const sf::Color& color, unsigned int charSize, const std::string& content, const Context& context);

	// Returns a random float between min and max
	static float random(float min, float max);

};