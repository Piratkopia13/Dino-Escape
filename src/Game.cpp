#include "Game.h"

int Game::m_fps = 0;

Game::Game()
: m_window(sf::VideoMode(1280, 720), "Look at me, I'm a window!")
, TimePerFrame(sf::seconds(1.0f/60.0f))
, m_stateStack(State::Context(m_window, m_textureManager, m_fontManager, m_levelManager, m_musicPlayer, m_soundPlayer))
{

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

}

void Game::run() {

	// Enable VSYNC
	m_window.setVerticalSyncEnabled(true);

	sf::Clock clock, fpsClock;
	sf::Time elapsedTime = sf::Time::Zero;

	int frames = 0;
	sf::Time startTime = sf::Time::Zero;

	while (m_window.isOpen()) {

		// Calculate FPS every 1/4th second
		if ((fpsClock.getElapsedTime() - startTime).asSeconds() > 0.25f && frames > 10) {
			m_fps = frames / (fpsClock.restart() - startTime).asSeconds();
			startTime = sf::Time::Zero;
			frames = 0;
		}
		frames++;

		// Update using a fixed timestep of TimePerFrame (1/60)
		elapsedTime += clock.restart();
		while (elapsedTime > TimePerFrame) {
			elapsedTime -= TimePerFrame;

			// Process events
			processEvents();
			// Update all the stuff
			update(TimePerFrame);
		}

		// Render
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

}
void Game::render() {

	m_window.clear(sf::Color(20, 20, 20));

	m_stateStack.draw();

#ifdef ENABLE_DEBUG_SHAPES
	// Draw debug shapes
	DebugRenderer::draw(m_window);
#endif

	m_window.display();

}

int Game::getFPS() {
	return m_fps;
}