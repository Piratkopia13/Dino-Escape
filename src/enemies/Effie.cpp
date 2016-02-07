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

	sf::Vector2f myPos = sprite.getPosition();
	sf::Vector2f playerPos = world->getPlayer()->getCenterPos();

	// Raycast
	bool rayIntersects = world->getMap()->isLineColliding(myPos, playerPos);

	if (!rayIntersects) {

		// Check what direction effie is looking
		if (playerPos.x < myPos.x) {
			// Flip
			sprite.setScale(-spriteScale.x, spriteScale.y);
		} else {
			// Flip back
			sprite.setScale(spriteScale.x, spriteScale.y);
		}

		// Play shoot animation
		sprite.play(shootAnimation);

		// Fire a bullet towards the player
		float bulletSpeed = 4.0f;
		sf::Vector2f bulletDir = Utils::normalize(playerPos - myPos);
		sf::Vector2f bulletVelocity = bulletSpeed * bulletDir;
		world->getBulletSystem().fireBullet(Bullet::FIREBALL, myPos, bulletVelocity, this);


	} else {
		sprite.play(walkAnimation);
	}
	sprite.update(dt);

}

void Effie::hitByBullet(Bullet* blt) {
	// TODO : make different bullet-types do different amount of damage
	health -= 1;

	if (health <= 0)
		isDead = true; // Tell GameWorld to remove this entity
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