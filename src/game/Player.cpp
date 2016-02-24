#include "Player.h"

Player::Player()
: m_BulletCooldown(sf::seconds(.4f))
, m_isLookingLeft(false)
, m_maxJumpTime(sf::seconds(.1f))
{

	sprite.setFrameTime(sf::seconds(.1f));
	sprite.pause();

	// Load texture
	m_spriteSheet.loadFromFile("res/textures/dino.png");
	
	// Set up animations
	m_walkingAnimation.setSpriteSheet(m_spriteSheet);
	m_walkingAnimation.createFrames(22, 22, 0, 22, 8);

	m_standingAnimation.setSpriteSheet(m_spriteSheet);
	m_standingAnimation.createFrames(22, 22, 0, 0, 8);

	m_shootAnimation.setSpriteSheet(m_spriteSheet);
	m_shootAnimation.createFrames(22, 22, 0, 44, 4);

	// Set inital animation
	currentAnimation = &m_standingAnimation;
	sprite.setAnimation(*currentAnimation);

	// Set origin / rotation point
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);

	// Set scale and starting position
	m_spriteScale = 1.55f;
	sprite.setScale(m_spriteScale, m_spriteScale);
	sprite.setPosition(100.0f, 200.0f);

	// Set inital health
	setHealth(6);

	// Set up entity properties
	hitByBulletXMultiplier = 4.f;
	invulnerableTime = sf::seconds(.3f);

	// Hardcoded bounding box size
	m_boundingBox = sprite.getGlobalBounds();
	m_boundingBox.width -= 15.0f;

}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed) {

	if (key == sf::Keyboard::W)
		m_isJumping = isPressed;
	if (key == sf::Keyboard::A)
		m_isMovingLeft = isPressed;
	if (key == sf::Keyboard::D)
		m_isMovingRight = isPressed;
	if (key == sf::Keyboard::Space)
		m_isShooting = isPressed;

}

void Player::update(const sf::Time& dt) {

	float speed = 187.0f * dt.asSeconds();
	sf::Vector2f targetSpeed;


	// ===================== //
	// ====== Jumping ====== //
	// ===================== //

	if (m_justJumped && !m_isJumping) {
		m_inJump = false;
		m_justJumped = false;
	}
	if (isGrounded()) {
		m_inJump = false;
		m_currentJumpTime = sf::Time::Zero;
	}
	if (m_isJumping) {

		if (isGrounded())
			// Play jump sound
			getGameWorld().getContext().sounds->play(Sounds::ID::Jump);

		m_justJumped = true;

		if (m_currentJumpTime <= m_maxJumpTime) {

			if (isGrounded() || m_inJump) {
			
				m_inJump = true;
				if (m_currentJumpTime == sf::Time::Zero) {

					velocity.y = -50.f; // Min jump height

				} else {
					velocity.y -= 1.f / (m_currentJumpTime.asSeconds() * 2.f); // Number fiddling to get the right feeling
				}

				m_currentJumpTime += dt;

			}

		}

	}
	if (isGrounded())
		m_currentJumpTime = sf::Time::Zero; // This needs to be here to reset the time if a new jump will occure next frame
	

	// ================================= //
	// ====== Horizontal movement ====== //
	// ================================= //

	bool isMovingHorizintally = false;
	if (m_isMovingLeft) {
		isMovingHorizintally = true;
		velocity.x -= speed;

		turn(true);
	}
	if (m_isMovingRight) {
		isMovingHorizintally = true;
		velocity.x += speed;

		turn(false);
	}
	if (!isMovingHorizintally && !m_isShooting)
		currentAnimation = &m_standingAnimation;



	if (m_isShooting) {
		fireGun();
	}

	// Update bullet cooldown
	m_lastBulletTime += dt;


	// Update parent
	Entity::update(dt);

}

void Player::hitByBullet(Bullet* blt) {

	// Call parent
	Entity::hitByBullet(blt);

}

void Player::fireGun() {

	if (m_lastBulletTime >= m_BulletCooldown) {

		// Play shoot sound
		getGameWorld().getContext().sounds->play(Sounds::ID::Shoot);

		// Fire a bullet in the direction I'm looking
		float bulletSpeed = 15.0f;

		sf::Vector2f from = getCenterPos();
		from.y -= 3.f; // shoot from the barrel
		sf::Vector2f bulletVelocity;
		if (m_isLookingLeft) {
			bulletVelocity.x = -bulletSpeed;
			from.x -= 15.0f;
		} else {
			bulletVelocity.x = bulletSpeed;
			from.x += 15.0f;
		}
		bulletVelocity += getLastVelocity();

		getGameWorld().getBulletSystem().fireBullet(Bullet::NORMAL, from, bulletVelocity, this);
			
		// Reset cooldown timer
		m_lastBulletTime = sf::Time::Zero;

		// Play shoot animation
		currentAnimation = &m_shootAnimation;

		// Sync animation with bullets
		sprite.setFrame(1, true);
	}

}

void Player::turn(bool left) {

	if (!m_isShooting) {
		currentAnimation = &m_walkingAnimation;
	}
	sprite.setScale((left) ? -m_spriteScale : m_spriteScale, m_spriteScale);
	m_isLookingLeft = left;

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	//DebugRenderer::addShape(sprite.getPosition(), sprite.getGlobalBounds(), sf::Color::Red);

	// Draw sprite from parent
	Entity::draw(target, states);

}

sf::Transformable& Player::getTransformable() {
	return sprite;
}
sf::FloatRect Player::getGlobalBounds() {

	// Hardcoded bounding box size
	sf::FloatRect& bb = sprite.getGlobalBounds();
	m_boundingBox.left = bb.left + m_boundingBox.width / 2.0f;
	m_boundingBox.top = bb.top;

	return m_boundingBox;
}
sf::Vector2f Player::getCenterPos() const {
	return sprite.getPosition();
}