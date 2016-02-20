#include "GameState.h"
#include "../Game.h"

GameState::GameState(StateStack& stack, Context context) 
: State(stack, context)
, m_map("level1.json")
, m_worldCamera(*context.window)
, m_hudCamera(*context.window)
, m_world(m_map, *context.textures)
, m_spawnClickEnt(m_world, *context.window)
, m_spawnClickBlt(m_world, *context.window)
, m_healthBar(context)
{

	// Set the cameras constraints to map border
	m_worldCamera.setConstraints(m_map.getBounds());
	m_worldCamera.zoom(1 / 2.5f);

	m_spawnClickEnt.setSpawnType(SpawnClickEntity::EFFIE);

	m_FPStext.setFont(getContext().fonts->get(FontManager::Emulogic));
	m_FPStext.setCharacterSize(15);
	m_FPStext.setPosition(0, getContext().window->getSize().y - 20.f);

	m_healthBar.setHealth(6);
	m_healthBar.setPosition(getContext().window->mapPixelToCoords(sf::Vector2i(15.f, 15.f)));

}
GameState::~GameState() {
}

bool GameState::handleEvent(const sf::Event& event) {

	sf::RenderWindow* window = getContext().window;

	switch (event.type) {

	case sf::Event::KeyPressed:
		m_world.handleInput(event.key.code, true);
		break;

	case sf::Event::KeyReleased:
		m_world.handleInput(event.key.code, false);
		break;

	case sf::Event::Resized:
		m_worldCamera.handleResize(event.size);
		m_hudCamera.handleResize(event.size);

		m_hudCamera.applyView();
		m_FPStext.setPosition(window->mapPixelToCoords(sf::Vector2i(0, window->getSize().y - 20.f)));
		m_healthBar.setPosition(window->mapPixelToCoords(sf::Vector2i(15.f, 15.f)));

		break;

	case sf::Event::MouseButtonPressed:
		m_worldCamera.applyView();
		m_spawnClickEnt.handleInput(event.mouseButton.button, true);
		m_spawnClickBlt.handleInput(event.mouseButton.button, true);
		break;

	case sf::Event::MouseButtonReleased:
		m_worldCamera.applyView();
		m_spawnClickEnt.handleInput(event.mouseButton.button, false);
		m_spawnClickBlt.handleInput(event.mouseButton.button, false);
		break;

	}

	return true;

}
bool GameState::update(sf::Time dt) {

	sf::RenderWindow* window = getContext().window;

	m_world.update(dt);
	m_worldCamera.moveTo(m_world.getPlayer()->getCenterPos());

	// Update FPSText
	m_FPStext.setString("FPS: " + std::to_string(Game::getFPS()));

	int playerHP = m_world.getPlayer()->health;
	m_healthBar.setHealth(playerHP);
	if (playerHP == 0) {
		requestStackPush(States::Death);
		m_world.getPlayer()->health = 6;
	}
	

	return true;
}
void GameState::draw() {

	sf::RenderWindow* window = getContext().window;

	// Apply world camera view
	m_worldCamera.applyView();

	window->draw(m_world);


	// Apply default camera view for HUD rendering
	m_hudCamera.applyView();

	window->draw(m_healthBar);

	// Render FPS
	window->draw(m_FPStext);

}