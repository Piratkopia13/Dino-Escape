#include "GameWorld.h"

const float GameWorld::GRAVITY = 340.0f;

GameWorld::GameWorld(TileMap& map)
: m_map(map)
{

}

void GameWorld::add(Entity* entity) {
	m_entities.push_back(entity);
	// Let the entity know what map it is on
	entity->map = &m_map;
}

void GameWorld::handleInput(sf::Keyboard::Key key, bool isPressed) {

	for (Entity* e : m_entities)
		e->handleInput(key, isPressed);

}

void GameWorld::update(sf::Time dt) {

	for (Entity* e : m_entities) {
		// Update
		e->update(dt);
		//// Perform custom map checks for entites that has it implented, like Blobber's AI
		//e->customMapCheck(m_map);
	}

	// Apply gravity and move by velocity
	for (Entity* e : m_entities) {

		// Apply gravity
		e->velocity.y += GRAVITY * dt.asSeconds();

		// Interpolate values to simulate acceleration
		float stepX = e->interpolationStepOnGround.x;
		if (!e->isGrounded) stepX = e->interpolationStepInAir.x; // Slower acceleration while in air
		e->velocity.y = e->interpolationStepOnGround.y * e->velocity.y + (1 - e->interpolationStepOnGround.y) * e->lastVelocity.y;
		e->velocity.x = stepX * e->velocity.x + (1 - stepX) * e->lastVelocity.x;

		// Move by velocity
		e->getTransformable().move(e->velocity);

		if (fabs(e->velocity.x) < 0.0001f) e->velocity.x = 0.f;
		if (fabs(e->velocity.y) < 0.0001f) e->velocity.y = 0.f;

		//std::cout << "Vel: " << e->velocity.x << ", " << e->velocity.y << std::endl;
		
		e->lastVelocity.x = e->velocity.x;
		e->lastVelocity.y = e->velocity.y;
	}

	// Resolve collisions
	for (Entity* e : m_entities) {
		sf::Vector2f velBack = m_map.resolveCollisions(*e);
		e->getTransformable().move(velBack);
		e->lastVelocity += velBack;

		// Cheaty way to check if entity is on the ground
		if (velBack.y < 0 && velBack.y > -0.6f)
			e->isGrounded = true;
		else 
			e->isGrounded = false;

		e->velocity.x = 0; e->velocity.y = 0; // Reset velocity
		if (fabs(e->lastVelocity.x) < 0.0001f) e->lastVelocity.x = 0.f;
		if (fabs(e->lastVelocity.y) < 0.0001f) e->lastVelocity.y = 0.f;
	}

}

void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// Draw map
	target.draw(m_map, states);

	// Draw entities
	for (Entity* e : m_entities)
		target.draw(*e, states);

}