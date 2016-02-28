#include "GameWorld.h"

const float GameWorld::GRAVITY = 340.0f;

GameWorld::GameWorld(TileMap& map, Context& context)
: m_map(map)
, m_context(context)
, m_isLevelComplete(false)
{
	// Create the player
	add(new Player());
	// Store a pointer to the unique_ptr's value
	m_player = m_entities.back().get();

	handleMapObjects();
}

GameWorld::~GameWorld() {

}

void GameWorld::handleMapObjects() {
	auto objects = m_map.getObjects();
	for (auto obj : objects) {

		if (obj.type == "Spawn") {

			if (obj.name == "Player")
				m_player->getTransformable().setPosition(obj.x, obj.y - m_player->getGlobalBounds().height);
			else if (obj.name == "Effie")
				add(new Effie(*this, sf::Vector2f(obj.x, obj.y)));
			else if(obj.name == "Blobber")
				add(new Blobber(*this, sf::Vector2f(obj.x, obj.y)));

		}

		if (obj.name == "Goal") {
			m_mapGoalBounds.left = obj.x;
			m_mapGoalBounds.top = obj.y;
			m_mapGoalBounds.width = obj.width;
			m_mapGoalBounds.height = obj.height;
		}

		if (obj.name == "DamageArea") {
			unsigned int dmg = 1;
			if (obj.properties.size() > 0 && obj.properties.at(0).name == "Damage")
				dmg = stoi(obj.properties.at(0).value);
			m_damageAreas.push_back(sf::FloatRect(obj.x, obj.y, obj.width, obj.height));
			m_areaDamages.push_back(dmg);
		}


	}
}

void GameWorld::add(Entity* entity) {
	m_entities.push_back(std::move(Entity::EntityPtr(entity)));
	// Let the entity know about this world
	m_entities.back()->setWorld(this);
}
void GameWorld::add(Entity::EntityPtr& entity) {
	m_entities.push_back(std::move(entity));
	// Let the entity know about this world
	m_entities.back()->setWorld(this);
}

void GameWorld::handleInput(sf::Keyboard::Key key, bool isPressed) {

	for (auto& e : m_entities)
		e->handleInput(key, isPressed);

}

void GameWorld::update(sf::Time dt) {

#ifdef ENABLE_DEBUG_SHAPES
	DebugRenderer::addShape(m_mapGoalBounds, sf::Color::Cyan);
#endif

	for (auto it = m_entities.begin(); it != m_entities.end();) {
		auto& e = *it;

		// Remove if entity is dead and not the player
		// Make sure the player does not get deleted since that will cause a crash
		if (e->m_isDead && e.get() != m_player) {
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
		if (!e->m_isGrounded) stepX = e->interpolationStepInAir.x; // Slower acceleration while in air
		e->velocity.y = e->interpolationStepOnGround.y * e->velocity.y + (1 - e->interpolationStepOnGround.y) * e->m_lastVelocity.y;
		e->velocity.x = stepX * e->velocity.x + (1 - stepX) * e->m_lastVelocity.x;

		// Move by velocity
		e->getTransformable().move(e->velocity);
		//std::cout << "Entity Y velocity: " << e->velocity.y << std::endl;

		// Reset values if they are really low
		if (fabs(e->velocity.x) < 0.0001f) e->velocity.x = 0.f;
		if (fabs(e->velocity.y) < 0.0001f) e->velocity.y = 0.f;

		// Set lastVelocity to current velocity
		e->m_lastVelocity.x = e->velocity.x;
		e->m_lastVelocity.y = e->velocity.y;
	

		// ========================================= //
		// ====== Resolve collisions with map ====== //
		// ========================================= //

		sf::Vector2f velBack = m_map.resolveCollisions(*e);
		e->getTransformable().move(velBack);
		e->m_lastVelocity += velBack;

		// Cheaty way to check if entity is on the ground
		if (e->m_isGroundedNextFrame) {
			e->m_isGrounded = true;
			e->m_isGroundedNextFrame = false;
		}
		if (velBack.y < 0.f)
			e->m_isGroundedNextFrame = true;
		else 
			e->m_isGrounded = false;

		// Reset velocity
		e->velocity.x = 0; e->velocity.y = 0;
		// Reset values if they are really low
		if (fabs(e->m_lastVelocity.x) < 0.0001f) e->m_lastVelocity.x = 0.f;
		if (fabs(e->m_lastVelocity.y) < 0.0001f) e->m_lastVelocity.y = 0.f;


		// ================================================ //
		// ====== Resolve collisions between entites ====== //
		// ================================================ //

		// THIS IS SLOOW
		//for (auto& otherEnt : m_entities) {
		//	// Dont check for collisions with itself
		//	if (e != otherEnt) {
		//		// Check for collision
		//		if (e->getGlobalBounds().intersects(otherEnt->getGlobalBounds())) {
		//			e->collidedWith(otherEnt.get());
		//		}
		//	}
		//}
		// THIS IS FASTER, only check with the player since thats the only collision that gets handled atm
		if (e.get() != m_player) {
			// Check for collision
			if (e->getGlobalBounds().intersects(m_player->getGlobalBounds())) {
				e->collidedWith(m_player);
			}
		}

		// Check for collision with damage areas
		for (unsigned int i = 0; i < m_damageAreas.size(); i++) {
			auto& area = m_damageAreas.at(i);
			auto& dmg = m_areaDamages.at(i);
			if (e->getGlobalBounds().intersects(area)) {
				e->damage(dmg);
			}
		}

		// Kill entities outside the map
		if (!m_map.getBounds().intersects(e->getGlobalBounds()))
			e->destroy();


	}


	// =========================== //
	// ====== Update sounds ====== //
	// =========================== //

	m_context.sounds->setListenerPosition(m_player->getCenterPos());


	// ======================================== //
	// ====== Check if player is in goal ====== //
	// ======================================== //

	if (m_player->getGlobalBounds().intersects(m_mapGoalBounds)) {

		// Set stats
		m_stats.health = m_player->getHealth();
		getContext().levels->setStats(m_stats);
		// Set level as complete, next frame will show the LevelCompleteState
		m_isLevelComplete = true;
	}

	// Update time stat
	m_stats.finishTime += dt;

	// ============================ //
	// ====== Update bullets ====== //
	// ============================ //

	m_bulletSystem.update(dt);
	m_bulletSystem.resolveCollisions(m_map, m_entities);


	// ===================================== //
	// ====== Update particle systems ====== //
	// ===================================== //

	for (auto it = m_particleSystems.begin(); it != m_particleSystems.end();) {
		
		auto& p = *it;

		// Update
		p->update(dt, m_map);

		// Remove if system has no particles left
		if (p->shouldBeRemoved()) {
			it = m_particleSystems.erase(it);
		} else ++it;

	}

}

void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// Draw map
	target.draw(m_map, states);

	// Draw entities
	for (auto& e : m_entities)
		target.draw(*e, states);

	// Draw bullets
	m_bulletSystem.draw(target, states);

	// Draw particles
	for (auto& p : m_particleSystems)
		target.draw(*p, states);

}

void GameWorld::addParticleSystem(const sf::Vector2f& centerPosition, const sf::Image& image, const sf::IntRect& imageRect, const sf::Vector2f& scale) {

	std::unique_ptr<ParticleSystem> system(new ParticleSystem(centerPosition, image, imageRect, scale));
	m_particleSystems.push_back(std::move(system));

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

int GameWorld::getNumEntites() const {
	return m_entities.size();
}
int GameWorld::getNumParticleSystems() const {
	return m_particleSystems.size();
}
int GameWorld::getNumParticles() const {
	int count = 0;
	for (auto& p : m_particleSystems)
		count += p->getNumParticles();
	return count;
}

Context& GameWorld::getContext() const {
	return m_context;
}

const bool GameWorld::isLevelComplete() const {
	return m_isLevelComplete;
}

void GameWorld::playerKilledEntity() {
	// Update stats
	m_stats.enemiesKilled++;
}
