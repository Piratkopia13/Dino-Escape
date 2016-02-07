#include "Game.h"

Game::Game()
	: m_window(sf::VideoMode(1280, 720), "Look at me, I'm a window!")
	, TimePerFrame(sf::seconds(1.0f/60.0f))
	, m_map("test.json")
	, m_camera(m_window)
	, m_blobber(sf::Vector2f(10, 300))
	, m_effie(sf::Vector2f(240, 280))
	, m_world(m_map)
	, m_spawnClickEnt(m_world, m_window)
	, m_spawnClickBlt(m_world, m_window)
{

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

	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;

	while (m_window.isOpen()) {

		processEvents();
		elapsedTime += clock.restart();
		while (elapsedTime > TimePerFrame) {
			elapsedTime -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		
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

	/*debugBB.setPosition(m_blobber.getCenterPos());
	debugBB.setSize(sf::Vector2f(m_blobber.getGlobalBounds().width, m_blobber.getGlobalBounds().height));
	debugBB.move(-debugBB.getSize() / 2.0f);*/

}
void Game::render() {

	m_window.clear(sf::Color(20, 20, 20));

	m_window.draw(m_world);

	//m_window.draw(debugBB);
	/*for (sf::RectangleShape s : m_map.debugShapes)
		m_window.draw(s);*/

//#ifdef RENDER_COLLISION_SHAPES
//#endif

	m_window.display();

}