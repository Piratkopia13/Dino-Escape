#include "HealthBar.h"

HealthBar::HealthBar(State::Context& context)
: m_context(context)
{

	m_healthBarAnim.setSpriteSheet(m_context.textures->get(TextureManager::HEALTH_BAR));
	m_healthBarAnim.addFrame(sf::IntRect(0, 0, 28, 7));
	m_healthBarAnim.addFrame(sf::IntRect(0, 7, 28, 7));
	m_healthBarAnim.addFrame(sf::IntRect(0, 14, 28, 7));
	m_healthBarAnim.addFrame(sf::IntRect(0, 21, 28, 7));
	m_healthBarAnim.addFrame(sf::IntRect(0, 28, 28, 7));
	m_healthBarAnim.addFrame(sf::IntRect(0, 35, 28, 7));

	m_healthBar.setAnimation(m_healthBarAnim);

	m_healthBar.setScale(7.f, 7.f);

}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	target.draw(m_healthBar, states);

}

void HealthBar::setHealth(int hp) {

	if (hp > 0 && hp <= 6) {
		m_healthBar.setFrame(hp - 1);
	}


}