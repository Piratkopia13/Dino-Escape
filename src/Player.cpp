#include "Player.h"

Player::Player()
: m_sprite(sf::seconds(0.1f), true, false)
{

	// Load texture
	m_walkingSheet.loadFromFile("res/textures/dino_walk_normal.png");
	// Set up animations
	m_walkingAnimation.setSpriteSheet(m_walkingSheet);
	int width = 22, height = 22;
	int startX = 5, startY = 4;
	int space = 10;
	for (int i = 0; i < 8; i++) {
		m_walkingAnimation.addFrame(sf::IntRect(startX + i * width + space * i, startY, width, height));
	}

	m_standingSheet.loadFromFile("res/textures/dino_stand_normal.png");
	m_standingAnimation.setSpriteSheet(m_standingSheet);
	width = 22; height = 22;
	startX = 5; startY = 4;
	for (int i = 0; i < 8; i++) {
		m_standingAnimation.addFrame(sf::IntRect(startX + i * width + space * i, startY, width, height));
	}

	m_turnSheet.loadFromFile("res/textures/dino_turn.png");
	m_turnAnimation.setSpriteSheet(m_turnSheet);
	width = 22; height = 22;
	startX = 5; startY = 4;
	for (int i = 0; i < 3; i++) {
		m_turnAnimation.addFrame(sf::IntRect(startX + i * width + space * i, startY, width, height));
	}

	// Set inital animation
	m_sprite.setAnimation(m_standingAnimation);

	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
	m_spriteScale = 1.5f;
	m_sprite.setScale(m_spriteScale, m_spriteScale);
	m_sprite.setPosition(100.0f, 200.0f);


}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed) {

	if (key == sf::Keyboard::W)
		m_isJumping = isPressed;
	if (key == sf::Keyboard::A)
		m_isMovingLeft = isPressed;
	if (key == sf::Keyboard::D)
		m_isMovingRight = isPressed;

}

void Player::update(sf::Time dt) {

	float speed = 187.0f * dt.asSeconds();
	sf::Vector2f targetSpeed;

	if (m_isJumping && isGrounded) {
		// TODO: fix jumping, make it smoother (and with normal values, looking at you, 9k)
		velocity.y = -9000.0f * dt.asSeconds();
	}
	bool isMovingHorizintally = false;
	if (m_isMovingLeft) {
		isMovingHorizintally = true;
		velocity.x += -speed;
		m_sprite.play(m_walkingAnimation);
		m_sprite.setScale(-m_spriteScale, m_spriteScale);
	}
	if (m_isMovingRight) {
		isMovingHorizintally = true;
		velocity.x += speed;
		m_sprite.play(m_walkingAnimation);
		m_sprite.setScale(m_spriteScale, m_spriteScale);
	}

	if (!isMovingHorizintally)
		m_sprite.play(m_standingAnimation);

	m_sprite.update(dt);

}

void Player::hitByBullet(Bullet* blt) {

	// TODO : make different bullet-types do different amount of damage
	health -= 1;

	//if (health <= 0)
	//	isDead = true; // Tell GameWorld to remove this entity

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite);
}

sf::Transformable& Player::getTransformable() {
	return m_sprite;
}
sf::FloatRect Player::getGlobalBounds() const {
	return m_sprite.getGlobalBounds();
}
sf::Vector2f Player::getCenterPos() const {
	return m_sprite.getPosition();
}