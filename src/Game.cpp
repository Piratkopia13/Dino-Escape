#include "Game.h"

Game::Game()
	: m_window(sf::VideoMode(1280, 720), "Look at me, I'm a window!")
	, TimePerFrame(sf::seconds(1.0f/60.0f))
	, m_map("test.json")
	, m_camera(m_window)
	, m_blobber(sf::Vector2f(50, 300))
	, m_effie(sf::Vector2f(240, 280))
	, m_world(m_map)
	, m_spawnClickEnt(m_world, m_window)
	, m_spawnClickBlt(m_world, m_window)
{

	m_font.loadFromFile("res/fonts/Roboto-Regular.ttf");
	m_FPStext.setFont(m_font);
	m_FPStext.setCharacterSize(30);
	m_FPStext.setScale(0.2f, 0.2f);

	// Plant the time seed
	srand(static_cast<unsigned int>(time(0)));

	m_world.add(&m_player);
	m_world.add(&m_blobber);
	m_world.add(&m_effie);
	//m_world.setPlayer(&m_player);

	debugBB.setOutlineColor(sf::Color::Green);
	debugBB.setOutlineThickness(-1.f);
	debugBB.setFillColor(sf::Color::Transparent);

	m_spawnClickEnt.setSpawnType(SpawnClickEntity::EFFIE);

}
void Game::run() {

	//m_window.setFramerateLimit(100);

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

			switch (event.type) {

			case sf::Event::KeyPressed:
				//m_player.handleInput(event.key.code, true);
				m_world.handleInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				//m_player.handleInput(event.key.code, false);
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
			case sf::Event::Closed:
				m_window.close();
				break;
			}

		}

}
void Game::update(sf::Time dt) {

	m_world.setPlayer(&m_player);

	m_world.update(dt);
	m_camera.moveTo(m_player.getCenterPos());

	// Update FPSText
	m_FPStext.setPosition(m_window.mapPixelToCoords(sf::Vector2i(0, 0)));
	m_FPStext.setString("FPS: " + std::to_string(m_fps));

}
void Game::render() {

	m_window.clear(sf::Color(20, 20, 20));

	m_window.draw(m_world);

	// Render FPS
	m_window.draw(m_FPStext);

	m_window.display();

}