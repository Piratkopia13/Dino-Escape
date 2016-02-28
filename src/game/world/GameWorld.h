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


class GameWorld : public sf::Drawable {

	public:
		static const float GRAVITY;

	public:
		GameWorld(TileMap& map, Context& context);
		~GameWorld();

		void handleInput(sf::Keyboard::Key key, bool isPressed);
		void add(Entity* entity);
		void add(Entity::EntityPtr& entity);
		void addParticleSystem(const sf::Vector2f& centerPosition, const sf::Image& image, const sf::IntRect& imageRect, const sf::Vector2f& scale);

		void update(sf::Time dt);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		BulletSystem& getBulletSystem();
		Entity* getPlayer() const;
		TileMap* getMap() const;
		int getNumEntites() const;
		int getNumParticleSystems() const;
		int getNumParticles() const;
		Context& getContext() const;
		const bool isLevelComplete() const;
		
		void playerKilledEntity();
	
	private:
		// Spawns entites specified by the map
		// Also moves the player to the specified spawn
		// Also stores the map goal bounds
		void handleMapObjects();

	private:
		std::vector<Entity::EntityPtr> m_entities;
		BulletSystem m_bulletSystem;

		std::vector<std::unique_ptr<ParticleSystem>> m_particleSystems;

		Entity* m_player; // Who enemies should attack and bullets collide with

		TileMap& m_map;
		Context& m_context;

		sf::FloatRect m_mapGoalBounds;
		std::vector<sf::FloatRect> m_damageAreas;
		std::vector<unsigned int> m_areaDamages;

		LevelManager::Stats m_stats;
		bool m_isLevelComplete;

};