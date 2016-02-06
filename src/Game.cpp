#include "Game.h"

Game::Game()
	: m_window(sf::VideoMode(1280, 720), "Look at me, I'm a window!")
	, TimePerFrame(sf::seconds(1.0f/60.0f))
	, m_map("test.json")
	, m_camera(m_window)
	, m_blobber(sf::Vector2f(100, 300))
	, m_effie(sf::Vector2f(50, 200))
	, m_world(m_map)
{

	m_world.add(&m_player);
	m_world.add(&m_blobber);
	m_world.add(&m_effie);

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
			case sf::Event::Closed:
				m_window.close();
				break;
			}

		}

}
void Game::update(sf::Time dt) {

	m_world.update(dt);
	m_camera.moveTo(m_player.getCenterPos());

}
void Game::render() {

	m_window.clear(sf::Color(20, 20, 20));

	m_window.draw(m_world);

#ifdef RENDER_COLLISION_SHAPES
	for (sf::RectangleShape s : m_player.debug_collisionShapes)
		m_window.draw(s);
#endif

	m_window.display();

}