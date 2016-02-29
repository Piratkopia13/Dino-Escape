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
, m_isPaused(false)
, m_deathTimer(sf::seconds(2.0f))
{

	// Set the cameras constraints to map border
	m_worldCamera.setConstraints(m_map.getBounds());
	m_worldCamera.lockHeight(192.f);

	// Update resolution in shader
	getContext().shaders->reload();
	getContext().shaders->get(PostEffects::Vignette).setParameter("resolution", sf::Vector2f(getContext().window->getSize()));

	m_spawnClickEnt.setSpawnType(SpawnClickEntity::BLOBBER);

	m_FPStext.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_FPStext.setCharacterSize(15);
	m_FPStext.setPosition(0, getContext().window->getSize().y - 20.f);


	m_entityCountText.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_entityCountText.setCharacterSize(15);
	m_entityCountText.setPosition(0, getContext().window->getSize().y - 40.f);

	m_particleCountText.setFont(getContext().fonts->get(Fonts::ID::Main));
	m_particleCountText.setCharacterSize(15);
	m_particleCountText.setPosition(0, getContext().window->getSize().y - 60.f);

	m_healthBar.setHealth(6);
	m_healthBar.setPosition(getContext().window->mapPixelToCoords(sf::Vector2i(15.f, 15.f)));

	m_vignetteShader = &context.shaders->get(PostEffects::Vignette);

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

		// Pause when escape is pressed
		if (!m_isPaused && m_world.getPlayer()->getHealth() > 0 && event.key.code == sf::Keyboard::Escape) {
			requestStackPush(States::Pause);
			m_isPaused = true;
		}

		break;

	case sf::Event::KeyReleased:
		m_world.handleInput(event.key.code, false);
		break;

	case sf::Event::Resized:
		m_worldCamera.handleResize(event.size);
		m_hudCamera.handleResize(event.size);

		window->setView(m_hudCamera.getView());
		m_FPStext.setPosition(window->mapPixelToCoords(sf::Vector2i(0.f, window->getSize().y - 20.f)));
		m_entityCountText.setPosition(window->mapPixelToCoords(sf::Vector2i(0.f, window->getSize().y - 40.f)));
		m_particleCountText.setPosition(window->mapPixelToCoords(sf::Vector2i(0.f, window->getSize().y - 60.f)));
		m_healthBar.setPosition(window->mapPixelToCoords(sf::Vector2i(15, 15)));

		// Update resolution in shader
		getContext().shaders->get(PostEffects::Vignette).setParameter("resolution", sf::Vector2f(event.size.width, event.size.height));

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

	// Set paused to false
	// This only runs when the pause menu is not active
	m_isPaused = false;

	sf::RenderWindow* window = getContext().window;

	// Update the player death "animation"
	if (m_hasStartedDeathAnimation && !m_hasFinishedDeathAnimation) {
		// Increase timer
		m_timeDead += dt;

		// If timer is done
		if (m_timeDead >= m_deathTimer) {
			// Switch to the death state
			requestStackPush(States::Death);
			m_hasFinishedDeathAnimation = true;
		}

		// Player has died, but the animation is not complete
		// Slooow moootiiooon!
		dt *= .2f;

	}

	// Update the world
	m_world.update(dt);
	
	// Check if the player has completed the level
	if (m_world.isLevelComplete()) {
		// Destroy this GameState instance
		// and show the level complete screen
		requestStackPop();
		requestStackPush(States::LevelComplete);
	}

	// Move the camera to the player's position
	m_worldCamera.moveTo(m_world.getPlayer()->getCenterPos());

	// Update FPSText
	m_FPStext.setString("FPS: " + std::to_string(Game::getFPS()));
	// Update entity count text
	m_entityCountText.setString("Entities: " + std::to_string(m_world.getNumEntites()));
	// Update particle count text
	m_particleCountText.setString("Particles: " + std::to_string(m_world.getNumParticles()) + "/" + std::to_string(m_world.getNumParticleSystems()));

	// Update healthbar
	Entity* player = m_world.getPlayer();
	m_healthBar.setHealth(player->getHealth());


	// Switch to death state when player dies
	if (player->isDead() && !m_hasStartedDeathAnimation) {

		// Zoom in
		m_worldCamera.zoom(.7f);

		// Stop music
		getContext().music->stop();
		// Play lose jingle
		getContext().sounds->play(Sounds::LoseJingle);

		m_hasStartedDeathAnimation = true;
	}
	
	// Update world camera
	m_worldCamera.update(dt);

	return true;
}
void GameState::draw() {

	sf::RenderWindow* window = getContext().window;

	// Apply world camera view
	window->setView(m_worldCamera.getView());

	try {
		m_vignetteShader = &getContext().shaders->get(PostEffects::Vignette);
	} catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	window->draw(m_world, m_vignetteShader);

	DRAW_DEBUG_IF_ENABLED(*window);

	// Apply default camera view for HUD rendering
	window->setView(m_hudCamera.getView());

	window->draw(m_healthBar);

	// Render FPS
	window->draw(m_FPStext);
	// Render entity count
	window->draw(m_entityCountText);
	// Render particle count
	window->draw(m_particleCountText);

}