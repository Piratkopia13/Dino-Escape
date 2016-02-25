#include "GameState.h"
#include "../Game.h"

GameState::GameState(StateStack& stack, Context& context) 
: State(stack, context)
, m_map(context.levels->getCurrentLevelFile()) // Load the currently set level
, m_worldCamera(*context.window)
, m_hudCamera(*context.window)
, m_world(m_map, context)
, m_spawnClickEnt(m_world, *context.window)
, m_spawnClickBlt(m_world, *context.window)
, m_healthBar(context)
{

	// Set the cameras constraints to map border
	m_worldCamera.setConstraints(m_map.getBounds());
	m_worldCamera.lockHeight(192.f);

	m_spawnClickEnt.setSpawnType(SpawnClickEntity::BLOBBER);

	m_FPStext.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_FPStext.setCharacterSize(15);
	m_FPStext.setPosition(0, getContext().window->getSize().y - 20.f);


	m_entityCountText.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_entityCountText.setCharacterSize(15);
	m_entityCountText.setPosition(0, getContext().window->getSize().y - 40.f);

	m_healthBar.setHealth(6);
	m_healthBar.setPosition(getContext().window->mapPixelToCoords(sf::Vector2i(15.f, 15.f)));

	// Play the Game music  theme
	getContext().music->play(Music::ID::GameTheme);

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

		window->setView(m_hudCamera.getView());
		m_FPStext.setPosition(window->mapPixelToCoords(sf::Vector2i(0, window->getSize().y - 20.f)));
		m_entityCountText.setPosition(window->mapPixelToCoords(sf::Vector2i(0, window->getSize().y - 40.f)));
		m_healthBar.setPosition(window->mapPixelToCoords(sf::Vector2i(15.f, 15.f)));

		break;

	case sf::Event::MouseButtonPressed:
		window->setView(m_worldCamera.getView());
		m_spawnClickEnt.handleInput(event.mouseButton.button, true);
		m_spawnClickBlt.handleInput(event.mouseButton.button, true);
		break;

	case sf::Event::MouseButtonReleased:
		window->setView(m_worldCamera.getView());
		m_spawnClickEnt.handleInput(event.mouseButton.button, false);
		m_spawnClickBlt.handleInput(event.mouseButton.button, false);
		break;

	}

	return true;

}
bool GameState::update(sf::Time dt) {

	sf::RenderWindow* window = getContext().window;

	m_world.update(dt);
	
	if (m_world.isLevelComplete()) {
		// Destroy this GameState instance
		// and show the level complete screen
		requestStackPop();
		requestStackPush(States::LevelComplete);
	}

	m_worldCamera.moveTo(m_world.getPlayer()->getCenterPos());

	// Update FPSText
	m_FPStext.setString("FPS: " + std::to_string(Game::getFPS()));

	// Update entity count text
	m_entityCountText.setString("Num entities: " + std::to_string(m_world.getNumEntites()));

	int playerHP = m_world.getPlayer()->getHealth();
	m_healthBar.setHealth(playerHP);
	if (playerHP == 0) {
		requestStackPush(States::Death);
		m_world.getPlayer()->setHealth(6);
	}
	

	return true;
}
void GameState::draw() {

	sf::RenderWindow* window = getContext().window;

	// Apply world camera view
	window->setView(m_worldCamera.getView());

	window->draw(m_world);

#ifdef ENABLE_DEBUG_SHAPES
	// Draw debug shapes
	DebugRenderer::draw(*window);
#endif

	// Apply default camera view for HUD rendering
	window->setView(m_hudCamera.getView());

	window->draw(m_healthBar);

	// Render FPS
	window->draw(m_FPStext);
	// Render entity count
	window->draw(m_entityCountText);

}