#include "Effie.h"

Effie::Effie(sf::Vector2f position)
	: Enemy(position) {

	// Set up animation
	int width = 16, height = 16;
	int startX = 0, startY = 16;
	/*for (int i = 0; i < 3; i++)
		m_walkAnimation.addFrame(sf::IntRect(startX + i * width, startY, width, height));*/

	// Possible idle animation, make it slow tho
	walkAnimation.addFrame(sf::IntRect(0, 16, width, height));
	walkAnimation.addFrame(sf::IntRect(32, 16, width, height));

	shootAnimation.setSpriteSheet(texture);
	shootAnimation.addFrame(sf::IntRect(48, 16, width, height));
	shootAnimation.addFrame(sf::IntRect(0, 16, width, height));
	shootAnimation.addFrame(sf::IntRect(32, 16, width, height));

	sprite.setAnimation(walkAnimation);

	sprite.setOrigin(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
	sprite.setScale(spriteScale);

	sprite.setFrameTime(sf::seconds(0.3f));

}

void Effie::update(sf::Time dt) {

	sf::Vector2f start = sprite.getPosition();
	sf::Vector2f end = player->getCenterPos();

	// Raycast
	bool rayIntersects = map->isLineColliding(start, end);

	if (!rayIntersects) {
		sprite.play(shootAnimation);

		// Check what direction effie is looking
		if (end.x < start.x) {
			// Flip
			sprite.setScale(-spriteScale.x, spriteScale.y);
		} else {
			// Flip back
			sprite.setScale(spriteScale.x, spriteScale.y);
		}

	} else {
		sprite.play(walkAnimation);
	}
	sprite.update(dt);

}

void Effie::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	target.draw(sprite);

}

sf::Transformable& Effie::getTransformable() {
	return sprite;
}
sf::FloatRect Effie::getGlobalBounds() const {
	return sprite.getGlobalBounds();
}
sf::Vector2f Effie::getCenterPos() const {
	return sprite.getPosition();
}