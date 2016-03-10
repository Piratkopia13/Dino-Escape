#include "HealthBar.h"

HealthBar::HealthBar(Context& context)
: m_context(context)
{

	// Set up animation with the different health states
	m_healthBarAnim.setSpriteSheet(m_context.textures->get(Textures::ID::HealthBar));
	m_healthBarAnim.addFrame(sf::IntRect(0, 0, 28, 7));
	m_healthBarAnim.addFrame(sf::IntRect(0, 7, 28, 7));
	m_healthBarAnim.addFrame(sf::IntRect(0, 14, 28, 7));
	m_healthBarAnim.addFrame(sf::IntRect(0, 21, 28, 7));
	m_healthBarAnim.addFrame(sf::IntRect(0, 28, 28, 7));
	m_healthBarAnim.addFrame(sf::IntRect(0, 35, 28, 7));

	// Set the sprite to use the animation
	m_healthBar.setAnimation(m_healthBarAnim);

	// Scale it
	m_healthBar.setScale(7.f, 7.f);

}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	// Use the transform
	states.transform *= getTransform();
	// Draw the sprite
	target.draw(m_healthBar, states);

}

void HealthBar::setHealth(int hp) {

	// Health values from 1 to 6 are valid frames (-1) in the animation
	if (hp > 0 && hp <= 6)
		m_healthBar.setFrame(hp - 1);
	else 
		m_healthBar.setFrame(0);


}