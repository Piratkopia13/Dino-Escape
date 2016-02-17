#pragma once

#include <cassert>

#include "../Common.h"
#include "../states/State.h"
#include "../animations/AnimatedSprite.hpp"

class HealthBar : public sf::Drawable, public sf::Transformable {

	public:
		HealthBar(State::Context& context);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void setHealth(int hp);

	private:
		State::Context& m_context;

		AnimatedSprite m_healthBar;
		Animation m_healthBarAnim;

};