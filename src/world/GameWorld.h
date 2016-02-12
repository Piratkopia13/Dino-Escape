#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Entity.h"
#include "TileMap.h"
#include "BulletSystem.h"
#include "../enemies/Effie.h"
#include "../enemies/Blobber.h"

class GameWorld : public sf::Drawable {

	public:
		static const float GRAVITY;

	public:
		GameWorld(TileMap& map);
		~GameWorld();

		void handleInput(sf::Keyboard::Key key, bool isPressed);
		void add(Entity* entity);
		void setPlayer(Entity* player);

		void update(sf::Time dt);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		BulletSystem& getBulletSystem();
		Entity* getPlayer() const;
		TileMap* getMap() const;

	private:
		// Spawns entites specified by the map
		// Also moves the player to the specified spawn
		// Also stores the map goal bounds
		void handleMapObjects();

	private:
		std::vector<Entity*> m_entities;
		BulletSystem m_bulletSystem;

		sf::Vector2f m_playerSpawn;
		Entity* m_player; // Keep track of who enemies should attack and bullets collide with

		TileMap& m_map;
		std::vector<Entity*> m_mapDefinedEntities;

		sf::FloatRect m_mapGoalBounds;


};