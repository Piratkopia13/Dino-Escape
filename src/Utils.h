#pragma once

#include <string>
#include <fstream>
#include <streambuf>

#include <SFML\Graphics.hpp>

struct Context;

// Contains various static utility methods
class Utils {

public:

	// Reads a file into a std::string
	// Returned string is allocated on heap and needs to be deleted by client
	static std::string readFile(const char* filepath);
	static float linearInterpolation(float from, float to, float step);
	static sf::Vector2f linearInterpolation(const sf::Vector2f& from, const sf::Vector2f& to, float step);

	static sf::Vector2f normalize(sf::Vector2f& vec);

	static std::string vecToString(const sf::Vector2f& vec);

	static void centerTextOrigin(sf::Text& text);

	static void createCenteredText(sf::Text& theText, const sf::Color& color, unsigned int charSize, const std::string& content, const Context& context);
	static void createText(sf::Text& theText, const sf::Color& color, unsigned int charSize, const std::string& content, const Context& context);

};