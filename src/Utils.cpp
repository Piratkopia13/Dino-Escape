#include "Utils.h"
#include "states/State.h"

std::string Utils::readFile(const char* filepath) {

	std::ifstream t(filepath);
	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve((unsigned int)t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;

}

float Utils::linearInterpolation(float from, float to, float step) {
	return (from*(1 - step) + to*step);
}
sf::Vector2f Utils::linearInterpolation(const sf::Vector2f& from, const sf::Vector2f& to, float step) {
	return sf::Vector2f(linearInterpolation(from.x, to.x, step), linearInterpolation(from.y, to.y, step));
}


sf::Vector2f Utils::normalize(sf::Vector2f& vec) {
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (length != 0)
		return sf::Vector2f(vec.x / length, vec.y / length);
	else
		return vec;
}

std::string Utils::vecToString(const sf::Vector2f& vec) {
	std::string str = "{";
	str += std::to_string(vec.x); str += ", "; str += std::to_string(vec.y); str += "}";
	return str;
}

void Utils::centerTextOrigin(sf::Text& text) {

	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

}

void Utils::createCenteredText(sf::Text& theText, const sf::Color& color, unsigned int charSize, const std::string& content, const Context& context) {

	theText.setFont(context.fonts->get(Fonts::ID::Main));
	theText.setColor(color);
	theText.setCharacterSize(charSize);
	theText.setString(content);
	Utils::centerTextOrigin(theText);

}

void Utils::createText(sf::Text& theText, const sf::Color& color, unsigned int charSize, const std::string& content, const Context& context) {

	theText.setFont(context.fonts->get(Fonts::ID::Main));
	theText.setColor(color);
	theText.setString(content);
	theText.setCharacterSize(charSize);

}
