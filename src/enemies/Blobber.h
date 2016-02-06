#pragma once

#include "Enemy.h"
#include "..\TileMap.h"

class Blobber : public Enemy {

	public:
		Blobber(sf::Vector2f position = sf::Vector2f(0, 0));

		virtual void update(sf::Time dt);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual sf::Transformable& getTransformable();
		virtual sf::FloatRect getGlobalBounds() const;
		virtual sf::Vector2f getCenterPos() const;
		
		void runAI();

	private:
		sf::RectangleShape m_debugPoint;

		bool m_isMovingLeft, m_isMovingRight;

};