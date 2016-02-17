#include "MenuState.h"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
{

	m_selectedLine.setFillColor(sf::Color(47, 181, 72, 255));
	m_selectedIndex = Options::Play;

	float halfWindowWidth = getContext().window->getSize().x / 2.0f;

	m_title.setFont(context.fonts->get(FontManager::Emulogic));
	m_title.setCharacterSize(80);
	m_title.setString("Dino Escape");
	Utils::centerTextOrigin(m_title);
	m_title.setColor(sf::Color(61, 212, 100, 255));;
	m_title.setPosition(halfWindowWidth, 150);

	m_titleShadow = m_title;
	m_titleShadow.setColor(sf::Color(0, 0, 0, 200));
	m_titleShadow.setPosition(halfWindowWidth + 8, 158);

	m_bg.setTexture(&getContext().textures->get(TextureManager::MENU_BACKGROUND));
	m_bg.setSize(sf::Vector2f(getContext().window->getSize().x, getContext().window->getSize().y));
	m_bg.setPosition(0, 0);


	sf::Text optionText("Play", getContext().fonts->get(FontManager::Emulogic), 35);
	Utils::centerTextOrigin(optionText);
	optionText.setPosition(halfWindowWidth, 300);
	m_optionTexts.push_back(optionText);

	optionText.setString("Controls");
	Utils::centerTextOrigin(optionText);
	optionText.setPosition(halfWindowWidth, 400);
	m_optionTexts.push_back(optionText);

	optionText.setString("Exit");
	Utils::centerTextOrigin(optionText);
	optionText.setPosition(halfWindowWidth, 500);
	m_optionTexts.push_back(optionText);

	updateSelected();

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
			case Options::Exit:
				requestStackPop();
				break;
			}

		}

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

	m_selectedLine.setSize(sf::Vector2f(m_optionTexts.at(m_selectedIndex).getLocalBounds().width, 4.0f));
	sf::FloatRect bounds = m_selectedLine.getLocalBounds();
	m_selectedLine.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	m_selectedLine.setPosition(m_optionTexts.at(m_selectedIndex).getPosition().x, 
		m_optionTexts.at(m_selectedIndex).getPosition().y + m_optionTexts.at(m_selectedIndex).getGlobalBounds().height);

}