#include "GameState.h"
#include "../Game.h"

GameState::GameState(StateStack& stack, Context& context) 
: State(stack, context)
, m_worldCamera(*context.window)
, m_hudCamera(*context.window)
, m_world(context)
, m_spawnClickEnt(m_world, *context.window)
, m_spawnClickBlt(m_world, *context.window)
, m_healthBar(context)
, m_isPaused(false)
, m_vsync(true)
, m_deathTimer(sf::seconds(2.0f))
{

	// Set the cameras constraints to map border
	m_worldCamera.setConstraints(m_world.getMap().getBounds());
	// Lock the height of the camera
	// The width will depend on the size of the window
	m_worldCamera.lockHeight(192.f);
	// Move the camera to the position of the player
	m_worldCamera.setPosition(m_world.getPlayer()->getCenterPos());
	
	// Update resolution in shader
	getContext().shaders->get(PostEffects::Vignette).setParameter("resolution", sf::Vector2f(getContext().window->getSize()));

	// Set up what entity to spawn when clicking
	m_spawnClickEnt.setSpawnType(SpawnClickEntity::BLOBBER);

	// Set up status texts
	Utils::createText(m_FPStext, sf::Color::White, 15, "", getContext());
	m_FPStext.setPosition(0, getContext().window->getSize().y - 20.f);

	Utils::createText(m_entityCountText, sf::Color::White, 15, "", getContext());
	m_entityCountText.setPosition(0, getContext().window->getSize().y - 40.f);

	Utils::createText(m_particleCountText, sf::Color::White, 15, "", getContext());
	m_particleCountText.setPosition(0, getContext().window->getSize().y - 60.f);

	// Set up the healthbar with full health
	m_healthBar.setHealth(6);
	m_healthBar.setPosition(getContext().window->mapPixelToCoords(sf::Vector2i(15, 15)));

	// Store a pointer to the vignette shader
	m_vignetteShader = &context.shaders->get(PostEffects::Vignette);

	// Play the Game music theme
	getContext().music->play(Music::ID::GameTheme);

}

bool GameState::handleEvent(const sf::Event& event) {

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	switch (event.type) {

	// Check if a key was pressed
	case sf::Event::KeyPressed:

		// Pass the event to the world, which in turn will pass it to entities
		m_world.handleInput(event.key.code, true);

		// Pause when escape is pressed
		if (!m_isPaused && m_world.getPlayer()->getHealth() > 0 && event.key.code == sf::Keyboard::Escape) {
			requestStackPush(States::Pause);
			m_isPaused = true;
		}

		// Toggle debug texts
		if (event.key.code == sf::Keyboard::F1)
			m_showDebugTexts = !m_showDebugTexts;

		// Disable FPS limit
		if (event.key.code == sf::Keyboard::F2)
			window->setFramerateLimit(0);

		// Enable FPS limit
		if (event.key.code == sf::Keyboard::F3)
			window->setFramerateLimit(100);

		// Toggle VSYNC
		if (event.key.code == sf::Keyboard::F4) {
			m_vsync = !m_vsync;
			window->setVerticalSyncEnabled(m_vsync);
		}

		// REMOVE THIS BIND ON FINAL PRODUCT!
		// Go to next level
		if (event.key.code == sf::Keyboard::PageUp) {
			getContext().levels->goToNextLevel();
			requestStackPop();
			requestStackPush(States::Game);
		}


		break;

	// Check if a key was released
	case sf::Event::KeyReleased:

		// Pass the event to the world, which in turn will pass it to entities
		m_world.handleInput(event.key.code, false);

		break;

	// Check if the window was resized
	case sf::Event::Resized:

		// Pass the new size to the world
		m_worldCamera.handleResize(event.size);
		// Pass the new size to the hud camera
		m_hudCamera.handleResize(event.size);

		// Switch view to the hud
		window->setView(m_hudCamera.getView());
		// Update positions for status texts
		m_FPStext.setPosition(window->mapPixelToCoords(sf::Vector2i(0, window->getSize().y - 20)));
		m_entityCountText.setPosition(window->mapPixelToCoords(sf::Vector2i(0, window->getSize().y - 40)));
		m_particleCountText.setPosition(window->mapPixelToCoords(sf::Vector2i(0, window->getSize().y - 60)));
		m_healthBar.setPosition(window->mapPixelToCoords(sf::Vector2i(15, 15)));

		// Update resolution in shader
		getContext().shaders->get(PostEffects::Vignette).setParameter("resolution", sf::Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height)));

		break;

	// Check if a button was pressed on the mouse
	case sf::Event::MouseButtonPressed:

		// Switch view to the world so that the spawn clickers can get the world coordinates from window coordinates
		window->setView(m_worldCamera.getView());
		// Pass event to the debug spawn clickers
		m_spawnClickEnt.handleInput(event.mouseButton.button, true);
		m_spawnClickBlt.handleInput(event.mouseButton.button, true);

		break;

	// Check if a button was released on the mouse
	case sf::Event::MouseButtonReleased:

		// Switch view to the world so that the spawn clickers can get the world coordinates from window coordinates
		window->setView(m_worldCamera.getView());
		// Pass event to the debug spawn clickers
		m_spawnClickEnt.handleInput(event.mouseButton.button, false);
		m_spawnClickBlt.handleInput(event.mouseButton.button, false);

		break;

	// Check if the focus was lost
	case sf::Event::LostFocus:

		// Pause the game if allowed
		if (!m_isPaused && m_world.getPlayer()->getHealth() > 0) {
			requestStackPush(States::Pause);
			m_isPaused = true;
		}

	}

	return true;

}
bool GameState::update(sf::Time dt) {

	// Set paused to false
	// This only runs when the pause menu is not active
	m_isPaused = false;

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Update the player death animation if needed
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
		requestStackPop();
		// Show the level complete screen
		requestStackPush(States::LevelComplete);
	}

	// Move the camera to the player's position
	m_worldCamera.moveTo(m_world.getPlayer()->getCenterPos());

	// Update FPS text
	m_FPStext.setString("FPS: " + std::to_string(Game::getFPS()) + ((m_vsync) ? " VSync on" : ""));
	// Update entity count text
	m_entityCountText.setString("Entities: " + std::to_string(m_world.getNumEntites()));
	// Update particle count text
	m_particleCountText.setString("Particles: " + std::to_string(m_world.getNumParticles()) + "/" + std::to_string(m_world.getNumParticleSystems()));

	// Get a pointer to the player
	Entity* player = m_world.getPlayer();
	// Update healthbar
	m_healthBar.setHealth(player->getHealth());

	// Start the death animation if the player just died
	if (player->isDead() && !m_hasStartedDeathAnimation) {

		// Zoom in camera
		m_worldCamera.zoom(.7f);

		// Stop music
		getContext().music->stop();
		// Play lose jingle
		getContext().sounds->play(Sounds::LoseJingle);

		// Flag that the animation has started
		m_hasStartedDeathAnimation = true;
	}
	
	// Update world camera
	m_worldCamera.update(dt);

	return true;
}
void GameState::draw() {

	// Get the window from the context
	sf::RenderWindow* window = getContext().window;

	// Switch view to the world
	window->setView(m_worldCamera.getView());

	// Draw the world with the shader applied
	window->draw(m_world, m_vignetteShader);

	// Draw debug shapes if they are enabled in Common.h
	DRAW_DEBUG_IF_ENABLED(*window);

	// Apply default camera view for HUD rendering
	window->setView(m_hudCamera.getView());

	// Draw the healthbar
	window->draw(m_healthBar);

	// Draw status texts if they should be drawn
	if (m_showDebugTexts) {
		// Render FPS
		window->draw(m_FPStext);
		// Render entity count
		window->draw(m_entityCountText);
		// Render particle count
		window->draw(m_particleCountText);
	}

}