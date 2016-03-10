#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "TileMap.h"
#include "BulletSystem.h"
#include "../../ParticleSystem.h"
#include "../../states/State.h"
#include "../Player.h"
#include "../enemies/Effie.h"
#include "../enemies/Blobber.h"

// The game world
// Handles everything that has to do with entities, collision resolving, particles, bullets etc.
class GameWorld : public sf::Drawable {

	public:
		// The gravity of the world
		// Defines how many pixels/second all entities will be moved down
		static const float GRAVITY;

	public:
		GameWorld(Context& context);

		// Passes the input to all entities
		void handleInput(sf::Keyboard::Key key, bool isPressed);
		// Adds an entity to the world
		// This moves the ownership of the pointer to the GameWorld
		void add(Entity* entity);
		void add(Entity::EntityPtr& entity);
		// Adds a particle system, based of an image, to the world
		void addParticleSystem(const sf::Vector2f& centerPosition, const sf::Image& image, const sf::IntRect& imageRect, const sf::Vector2f& scale);

		// Updates the world with all of its ramifications
		void update(sf::Time dt);
		// Draws the world
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// Getters
		BulletSystem& getBulletSystem();
		Entity* getPlayer() const;
		TileMap& getMap();
		int getNumEntites() const;
		int getNumParticleSystems() const;
		int getNumParticles() const;
		Context& getContext() const;
		const bool isLevelComplete() const;
		
		// Should be called when a player kills an entity
		// Will update the statistics
		void playerKilledEntity();
	
	private:
		// Spawns entites specified by the map
		// Also moves the player to the specified spawn
		// Also stores the map goal bounds and damage areas
		void handleMapObjects();

	private:
		// A list of smart pointers to entities
		std::vector<Entity::EntityPtr> m_entities;
		// The bullet system
		BulletSystem m_bulletSystem;

		// A list of smart pointers to particle systems
		std::vector<std::unique_ptr<ParticleSystem>> m_particleSystems;

		// Pointer to the player
		// This is who enemies should attack and bullets collide with
		Entity* m_player;

		// The tile map
		TileMap m_map;
		// A reference to the context
		Context& m_context;

		// The bounding box of the goal
		sf::FloatRect m_mapGoalBounds;
		// A list of all damage areas on the map
		std::vector<sf::FloatRect> m_damageAreas;
		// A list of the damage each damage are should do to entities
		// Has the same order as m_damageAreas
		std::vector<unsigned int> m_areaDamages;

		// Statistics for the current level
		LevelManager::Stats m_stats;
		// Flag it the map is complete
		bool m_isLevelComplete;

};