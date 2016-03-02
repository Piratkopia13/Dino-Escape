#include "ControlsState.h"

ControlsState::ControlsState(StateStack& stack, Context& context)
	: State(stack, context) {

	m_selectedLine.setFillColor(sf::Color(47, 181, 72, 255));

	m_bgImg.setTexture(&getContext().textures->get(Textures::ID::ControlsBackground));
	m_bg.setFillColor(sf::Color(2, 23, 33, 255));

	Utils::createCenteredText(m_backText, sf::Color::White, 35, "Back", getContext());

	m_selectedLine.setSize(sf::Vector2f(m_backText.getLocalBounds().width, 4.0f));
	sf::FloatRect bounds = m_selectedLine.getLocalBounds();
	m_selectedLine.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	
	setPositions();

}

ControlsState::~ControlsState() {
}

bool ControlsState::handleEvent(const sf::Event& event) {

	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::Return)
			requestStackPop();
		else if (event.key.code == sf::Keyboard::Escape)
			requestStackPop();

	} else if (event.type == sf::Event::Resized) {

		// Update text positions
		setPositions();

	}

	return false;
}

bool ControlsState::update(sf::Time dt) {

	return false;
}

void ControlsState::draw() {

	sf::RenderWindow* window = getContext().window;

	window->draw(m_bg);
	window->draw(m_bgImg);
	window->draw(m_backText);
	window->draw(m_selectedLine);

}

void ControlsState::setPositions() {

	sf::RenderWindow* window = getContext().window;

	int width = window->getSize().x;
	int height = window->getSize().y;
	window->setView(sf::View(sf::FloatRect(0.f, 0.f, width, height)));

	float halfWindowWidth = width / 2.0f;

	int imgWidth = m_bgImg.getTexture()->getSize().x;
	int imgHeight = m_bgImg.getTexture()->getSize().y;
	float aspectRatio = (float)imgWidth / imgHeight;

	m_bgImg.setSize(sf::Vector2f(height * aspectRatio, height));
	m_bgImg.setPosition(halfWindowWidth - m_bgImg.getSize().x / 2.f, 0.f);

	m_bg.setSize(sf::Vector2f(width, height));


	// Update positions for back text

	Utils::centerTextOrigin(m_backText);
	m_backText.setPosition(halfWindowWidth, height - 50.f);

	m_selectedLine.setPosition(halfWindowWidth, height - 50.f + m_backText.getGlobalBounds().height);


}