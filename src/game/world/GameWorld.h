#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "TileMap.h"
#include "BulletSystem.h"
#include "../../states/State.h"
#include "../Player.h"
#include "../enemies/Effie.h"
#include "../enemies/Blobber.h"


class GameWorld : public sf::Drawable {

	public:
		static const float GRAVITY;

	public:
		GameWorld(TileMap& map, State::Context& context);
		~GameWorld();

		void handleInput(sf::Keyboard::Key key, bool isPressed);
		void add(Entity* entity);
		void add(Entity::EntityPtr& entity);

		void update(sf::Time dt);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		BulletSystem& getBulletSystem();
		Entity* getPlayer() const;
		TileMap* getMap() const;
		int getNumEntites() const;
		State::Context& getContext() const;
		const bool isLevelComplete() const;

	private:
		// Spawns entites specified by the map
		// Also moves the player to the specified spawn
		// Also stores the map goal bounds
		void handleMapObjects();

	private:
		std::vector<Entity::EntityPtr> m_entities;
		BulletSystem m_bulletSystem;

		Entity* m_player; // Who enemies should attack and bullets collide with

		TileMap& m_map;
		State::Context& m_context;

		sf::FloatRect m_mapGoalBounds;


		bool m_isLevelComplete;

};