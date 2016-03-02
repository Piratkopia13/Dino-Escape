#include "MenuState.h"

MenuState::MenuState(StateStack& stack, Context& context)
: State(stack, context)
{

	m_selectedLine.setFillColor(sf::Color(47, 181, 72, 255));
	m_selectedIndex = Options::Play;

	m_title.setFont(context.fonts->get(Fonts::ID::Main));
	m_title.setCharacterSize(80);
	m_title.setString("Dino Escape");
	m_title.setColor(sf::Color(61, 212, 100, 255));;
	Utils::centerTextOrigin(m_title);

	m_titleShadow = m_title;
	m_titleShadow.setColor(sf::Color(0, 0, 0, 200));

	m_bg.setTexture(&getContext().textures->get(Textures::ID::MenuBackground));

	sf::Text optionText("Play", getContext().fonts->get(Fonts::ID::Main), 35);
	Utils::centerTextOrigin(optionText);
	m_optionTexts.push_back(optionText);

	optionText.setString("Controls");
	Utils::centerTextOrigin(optionText);
	m_optionTexts.push_back(optionText);

	optionText.setString("Exit");
	Utils::centerTextOrigin(optionText);
	m_optionTexts.push_back(optionText);

	setPositions();

	updateSelected();


	// Play the menu theme
	getContext().music->play(Music::ID::MenuTheme);

}

MenuState::~MenuState() {
}

bool MenuState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::Up) {
			if (m_selectedIndex > 0)
				m_selectedIndex--;
			else
				m_selectedIndex = m_optionTexts.size() - 1;

			updateSelected();

		} else if (event.key.code == sf::Keyboard::Down) {
			if (m_selectedIndex < m_optionTexts.size() - 1)
				m_selectedIndex++;
			else
				m_selectedIndex = 0;

			updateSelected();

		} else if (event.key.code == sf::Keyboard::Return) {
			
			switch (m_selectedIndex) {
			case Options::Play:
				requestStackPop();
				requestStackPush(States::Game);
				break;
			case Options::Controls:
				requestStackPush(States::Controls);
				break;
			case Options::Exit:
				requestStackPop();
				break;
			}

		}

	} else if (event.type == sf::Event::Resized) {

		// Update text positions
		setPositions();
		updateSelected();

	}

	return true;
}

bool MenuState::update(sf::Time dt) {
	
	return true;
}

void MenuState::draw() {

	sf::RenderWindow* window = getContext().window;

	window->draw(m_bg);
	window->draw(m_titleShadow);
	window->draw(m_title);

	for (auto& text : m_optionTexts) {
		window->draw(text);
	}

	window->draw(m_selectedLine);

}

void MenuState::updateSelected() {

	// Play select sound
	getContext().sounds->play(Sounds::Select);

	m_selectedLine.setSize(sf::Vector2f(m_optionTexts.at(m_selectedIndex).getLocalBounds().width, 4.0f));
	sf::FloatRect bounds = m_selectedLine.getLocalBounds();
	m_selectedLine.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	m_selectedLine.setPosition(m_optionTexts.at(m_selectedIndex).getPosition().x, 
		m_optionTexts.at(m_selectedIndex).getPosition().y + m_optionTexts.at(m_selectedIndex).getGlobalBounds().height);

}

void MenuState::setPositions() {

	sf::RenderWindow* window = getContext().window;

	int width = window->getSize().x;
	int height = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0.f, 0.f, width, height)));

	float halfWindowWidth = window->getSize().x / 2.0f;

	m_title.setPosition(halfWindowWidth, 150);
	Utils::centerTextOrigin(m_title);

	m_titleShadow.setPosition(halfWindowWidth + 8, 158);


	// Set background size depending on window size to keep image aspect ratio

	int imgWidth = m_bg.getTexture()->getSize().x;
	int imgHeight = m_bg.getTexture()->getSize().y;
	float aspectRatio = imgHeight / (float)imgWidth;

	if (height < width * aspectRatio)
		m_bg.setSize(sf::Vector2f(width, width * aspectRatio));
	else
		m_bg.setSize(sf::Vector2f(height * (1.f / aspectRatio), height));
	m_bg.setPosition(0, 0);


	// Update positions for options texts

	Utils::centerTextOrigin(m_optionTexts[Play]);
	m_optionTexts[Play].setPosition(halfWindowWidth, 300);

	Utils::centerTextOrigin(m_optionTexts[Controls]);
	m_optionTexts[Controls].setPosition(halfWindowWidth, 400);

	Utils::centerTextOrigin(m_optionTexts[Exit]);
	m_optionTexts[Exit].setPosition(halfWindowWidth, 500);


}