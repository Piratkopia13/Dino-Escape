#pragma once

#include <cassert>

#include "../Common.h"
#include "../states/State.h"
#include "../animations/AnimatedSprite.hpp"

// A drawable healthbar
// Shows a sprite depending on the set health (max is 6hp)
class HealthBar : public sf::Drawable, public sf::Transformable {

	public:
		HealthBar(Context& context);

		// Draws the healthbar
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		// Sets the health that will update the sprite
		void setHealth(int hp);

	private:
		Context& m_context;

		// Animated sprite used to store the different sprites
		AnimatedSprite m_healthBar;
		Animation m_healthBarAnim;

};