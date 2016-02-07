#pragma once

#include <string>
#include <fstream>
#include <streambuf>

#include <SFML\Graphics.hpp>

// Contains various static utility methods
class Utils {

public:

	// Reads a file into a std::string
	// Returned string is allocated on heap and needs to be deleted by client
	static std::string readFile(const char* filepath) {

		std::ifstream t(filepath);
		std::string str;

		t.seekg(0, std::ios::end);
		str.reserve((unsigned int)t.tellg());
		t.seekg(0, std::ios::beg);

		str.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		return str;

	}

	static float linearInterpolation(float from, float to, float step) {
		return (from*(1 - step) + to*step);
	}
	static sf::Vector2f linearInterpolation(const sf::Vector2f& from, const sf::Vector2f& to, float step) {
		return sf::Vector2f(linearInterpolation(from.x, to.x, step), linearInterpolation(from.y, to.y, step));
	}


	static sf::Vector2f normalize(sf::Vector2f& vec) {
		float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));
		if (length != 0)
			return sf::Vector2f(vec.x / length, vec.y / length);
		else
			return vec;
	}
};