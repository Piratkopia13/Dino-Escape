#include "GameWorld.h"

const float GameWorld::GRAVITY = 340.0f;

GameWorld::GameWorld(TileMap& map)
: m_map(map)
{
}

GameWorld::~GameWorld() {

	// Remove entities that where created from spawnpoints on the map
	for (auto e : m_mapDefinedEntities)
		delete e;

}

void GameWorld::spawnMapEntities() {
	auto objects = m_map.getObjects();
	for (auto obj : objects) {

		for (auto prop : obj.properties) {

			if (prop.name == "spawn") {

				if (prop.value == "player")
				m_player->getTransformable().setPosition(obj.x, obj.y - m_player->getGlobalBounds().height);
				if (prop.value == "effie") {
					m_mapDefinedEntities.push_back(new Effie(sf::Vector2f(obj.x, obj.y)));
					add(m_mapDefinedEntities.back());
				}
				if (prop.value == "blobber") {
					m_mapDefinedEntities.push_back(new Blobber(sf::Vector2f(obj.x, obj.y)));
					add(m_mapDefinedEntities.back());
				}
			}

		}

	}
}

void GameWorld::add(Entity* entity) {
	m_entities.push_back(entity);
	// Let the entity know about this world
	entity->world = this;
}

void GameWorld::setPlayer(Entity* player) {
	m_player = player;	
}


void GameWorld::handleInput(sf::Keyboard::Key key, bool isPressed) {

	for (Entity* e : m_entities)
		e->handleInput(key, isPressed);

}

void GameWorld::update(sf::Time dt) {

	for (auto it = m_entities.begin(); it != m_entities.end();) {
		Entity* e = *it;

		// Remove if entity is dead
		if (e->isDead) {
			it = m_entities.erase(it);
			continue;
		} else ++it;

		// Update
		e->update(dt);

		// ======================================== //
		// == Apply gravity and move by velocity == //
		// ======================================== //

		// Apply gravity
		e->velocity.y += GRAVITY * dt.asSeconds();

		// Interpolate values to simulate acceleration
		float stepX = e->interpolationStepOnGround.x;
		if (!e->isGrounded) stepX = e->interpolationStepInAir.x; // Slower acceleration while in air
		e->velocity.y = e->interpolationStepOnGround.y * e->velocity.y + (1 - e->interpolationStepOnGround.y) * e->lastVelocity.y;
		e->velocity.x = stepX * e->velocity.x + (1 - stepX) * e->lastVelocity.x;

		// Move by velocity
		e->getTransformable().move(e->velocity);

		// Reset values if they are really low
		if (fabs(e->velocity.x) < 0.0001f) e->velocity.x = 0.f;
		if (fabs(e->velocity.y) < 0.0001f) e->velocity.y = 0.f;

		//std::cout << "Vel: " << e->velocity.x << ", " << e->velocity.y << std::endl;
		
		// Set lastVelocity to current velocity
		e->lastVelocity.x = e->velocity.x;
		e->lastVelocity.y = e->velocity.y;
	

		// ================================ //
		// ====== Resolve collisions ====== //
		// ================================ //

		sf::Vector2f velBack = m_map.resolveCollisions(*e);
		e->getTransformable().move(velBack);
		e->lastVelocity += velBack;

		// Cheaty way to check if entity is on the ground
		if (velBack.y < 0 && velBack.y > -0.6f)
			e->isGrounded = true;
		else 
			e->isGrounded = false;

		// Reset velocity
		e->velocity.x = 0; e->velocity.y = 0;
		// Reset values if they are really low
		if (fabs(e->lastVelocity.x) < 0.0001f) e->lastVelocity.x = 0.f;
		if (fabs(e->lastVelocity.y) < 0.0001f) e->lastVelocity.y = 0.f;

	}

	// Bullet stuff
	m_bulletSystem.update(dt);
	m_bulletSystem.resolveCollisions(m_map, m_entities);

}

void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// Draw map
	target.draw(m_map, states);

	// Draw entities
	for (Entity* e : m_entities)
		target.draw(*e, states);

	// Draw bullets
	m_bulletSystem.draw(target, states);

}

BulletSystem& GameWorld::getBulletSystem() {
	return m_bulletSystem;
}
Entity* GameWorld::getPlayer() const {
	return m_player;
}
TileMap* GameWorld::getMap() const {
	return &m_map;
}