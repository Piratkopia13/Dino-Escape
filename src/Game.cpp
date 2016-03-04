#include "Game.h"

int Game::m_fps = 0;

Game::Game()
: m_window(sf::VideoMode(1280, 720), "Look at me, I'm a window!")
, m_soundPlayer() // Initialize sound after the window
, m_musicPlayer() // Initialize music after the window
, TimePerFrame(sf::seconds(1.0f/60.0f))
, m_stateStack(Context(m_window, m_textureManager, m_fontManager, m_levelManager, m_musicPlayer, m_soundPlayer, m_postEffectManager))
{

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

	// Set FPS limit
	//m_window.setFramerateLimit(100);

	sf::Clock updateClock, fpsClock;
	sf::Time elapsedUpdateTime = sf::Time::Zero;

	int frames = 0;
	sf::Time startTime = sf::Time::Zero;

	while (m_window.isOpen()) {

		// Update using a fixed timestep of TimePerFrame (1/60)
		elapsedUpdateTime += updateClock.restart();
		while (elapsedUpdateTime > TimePerFrame) {
			elapsedUpdateTime -= TimePerFrame;

			// Process events
			processEvents();
			// Update all the stuff
			update(TimePerFrame);
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

			m_stateStack.handleEvent(event);
			
			if (event.type == sf::Event::Closed)
				m_window.close();

		}

}
void Game::update(sf::Time dt) {

#ifdef ENABLE_DEBUG_SHAPES
	DebugRenderer::reset();
#endif

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

	m_window.clear(sf::Color(2, 23, 33));

	m_stateStack.draw();

	m_window.display();

}

int Game::getFPS() {
	return m_fps;
}