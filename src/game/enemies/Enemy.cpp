#include "Enemy.h"
#include "..\world\GameWorld.h"

Enemy::Enemy(GameWorld& world) {

	this->world = &world;

	// Set default enemy texture
	enemiesTexture = &world.getContext().textures->get(Textures::ID::ENEMIES);

}