#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Entity.h"
#include "TileMap.h"
#include "BulletSystem.h"

class GameWorld : public sf::Drawable {

	public:
		static const float GRAVITY;

	public:
		GameWorld(TileMap& map);

		void handleInput(sf::Keyboard::Key key, bool isPressed);
		void add(Entity* entity);
		void setPlayer(Entity* player);

		void update(sf::Time dt);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		BulletSystem& getBulletSystem();
		Entity* getPlayer() const;
		TileMap* getMap() const;

	private:
		std::vector<Entity*> m_entities;
		Entity* m_player; // Keep track of who enemies should attack and bullets collide with
		TileMap& m_map;
		BulletSystem m_bulletSystem;

};