#include "GameState.h"
#include "Game.h"

GameState::GameState(StateStack& stack, Context context) 
: State(stack, context)
, m_map("test.json")
, m_camera(*context.window)
, m_world(m_map, *context.textures)
, m_spawnClickEnt(m_world, *context.window)
, m_spawnClickBlt(m_world, *context.window)
{

	// Set the cameras constraints to map border
	m_camera.setConstraints(m_map.getBounds());
	m_camera.zoom(1 / 1.2f);

	m_spawnClickEnt.setSpawnType(SpawnClickEntity::EFFIE);

	m_FPStext.setFont(getContext().fonts->get(FontManager::Emulogic));
	m_FPStext.setCharacterSize(60);
	m_FPStext.setScale(0.1f, 0.1f);

}
GameState::~GameState() {
}

bool GameState::handleEvent(const sf::Event& event) {

	switch (event.type) {

	case sf::Event::KeyPressed:
		m_world.handleInput(event.key.code, true);
		break;

	case sf::Event::KeyReleased:
		m_world.handleInput(event.key.code, false);
		break;

	case sf::Event::Resized:
		m_camera.handleResize(event.size);
		break;

	case sf::Event::MouseButtonPressed:
		m_spawnClickEnt.handleInput(event.mouseButton.button, true);
		m_spawnClickBlt.handleInput(event.mouseButton.button, true);
		break;

	case sf::Event::MouseButtonReleased:
		m_spawnClickEnt.handleInput(event.mouseButton.button, false);
		m_spawnClickBlt.handleInput(event.mouseButton.button, false);
		break;

	}

	return true;

}
bool GameState::update(sf::Time dt) {

	m_world.update(dt);
	m_camera.moveTo(m_world.getPlayer()->getCenterPos());

	// Update FPSText
	m_FPStext.setPosition(getContext().window->mapPixelToCoords(sf::Vector2i(0, 0)));
	m_FPStext.move(2.0f, 0);
	m_FPStext.setString("FPS: " + std::to_string(Game::getFPS()));

	return true;
}
void GameState::draw() {

	sf::RenderWindow* window = getContext().window;

	window->draw(m_world);

	// Render FPS
	window->draw(m_FPStext);

}