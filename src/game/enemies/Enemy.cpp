#include "Enemy.h"
#include "..\world\GameWorld.h"

Enemy::Enemy(GameWorld& world) {

	setWorld(&world);

	// Set default enemy texture
	enemiesTexture = &getGameWorld().getContext().textures->get(Textures::ID::Enemies);

}