#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Entity.h"
#include "TileMap.h"

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

	private:
		std::vector<Entity*> m_entities;
		TileMap& m_map;

};