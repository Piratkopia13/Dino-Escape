#include "Game.h"

int Game::m_fps = 0;

Game::Game()
: m_window(sf::VideoMode(1280, 720), "Dino Escape") // Set up window with size and title
, m_soundPlayer() // Initialize sound after the window
, m_musicPlayer() // Initialize music after the window
, TimePerUpdate(sf::seconds(1.0f/60.0f)) // Set the fixed update delta to 60 updates per second
, m_stateStack(Context(m_window, m_textureManager, m_fontManager, m_levelManager, m_musicPlayer, m_soundPlayer, m_postEffectManager)) // Set up the context
{

	// Print out window settings for debug purposes
	sf::ContextSettings settings = m_window.getSettings();
	std::cout << "===== Window settings =====" << std::endl << std::endl;
	std::cout << "Depth bits: " << settings.depthBits << std::endl;
	std::cout << "Stencil bits: " << settings.stencilBits << std::endl;
	std::cout << "Antialiasing level: " << settings.antialiasingLevel << std::endl;
	std::cout << "OpenGL version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;
	std::cout << std::endl << "===========================" << std::endl;

	// Plant the time seed
	srand(static_cast<unsigned int>(time(0)));

	// Register states
	registerStates();
	// Set starting state
	m_stateStack.pushState(States::Menu);

}

void Game::registerStates() {

	// Register all of the different states
	m_stateStack.registerState<GameState>(States::Game);
	m_stateStack.registerState<DeathState>(States::Death);
	m_stateStack.registerState<LevelCompleteState>(States::LevelComplete);
	m_stateStack.registerState<MenuState>(States::Menu);
	m_stateStack.registerState<ControlsState>(States::Controls);
	m_stateStack.registerState<PauseState>(States::Pause);

}

void Game::run() {

	// Enable VSYNC
	m_window.setVerticalSyncEnabled(true);

	// Clocks for time calculations
	sf::Clock updateClock, fpsClock;
	sf::Time elapsedUpdateTime = sf::Time::Zero;

	// Frame counter
	int frames = 0;
	sf::Time startTime = sf::Time::Zero;

	// Game loop
	while (m_window.isOpen()) {

		// Update using a fixed timestep of TimePerUpdate (1/60)
		elapsedUpdateTime += updateClock.restart();
		while (elapsedUpdateTime > TimePerUpdate) {
			elapsedUpdateTime -= TimePerUpdate;

			// Process events
			processEvents();
			// Update all the stuff
			update(TimePerUpdate);
		}

		// Calculate FPS every 1/4th second
		if ((fpsClock.getElapsedTime() - startTime).asSeconds() > 0.25f && frames > 10) {
			m_fps = static_cast<int>(frames / (fpsClock.restart() - startTime).asSeconds());
			startTime = sf::Time::Zero;
			frames = 0;
		}
		frames++;

		// Render all the stuff
		render();

	}

}

void Game::processEvents() {

		sf::Event event;
		while (m_window.pollEvent(event)) {

			// Handle the event through the stack
			m_stateStack.handleEvent(event);
			
			// Close the window when the closed button is pressed
			if (event.type == sf::Event::Closed)
				m_window.close();

		}

}
void Game::update(sf::Time dt) {

#ifdef ENABLE_DEBUG_SHAPES
	// Reset the debug renderer
	DebugRenderer::reset();
#endif

	// Update through the stack
	m_stateStack.update(dt);
	
	// Exit game when state stack is empty
	if (m_stateStack.isEmpty()) {
		std::cout << "Stack is empty, quitting." << std::endl;
		m_window.close();
	}

	// Remove stopped sounds
	m_soundPlayer.removeStoppedSounds();

}
void Game::render() {

	// Clear the window with a nice color that matches the map tileset
	m_window.clear(sf::Color(2, 23, 33));

	// Draw the stack
	m_stateStack.draw();

	// Update the display
	m_window.display();

}

int Game::getFPS() {
	return m_fps;
}