#include "Enemy.h"
#include "..\world\GameWorld.h"

Enemy::Enemy(GameWorld& world)
: spriteScale(2.0f, 2.0f) // Default sprite scale
{

	// Set the world that the entity is in
	setWorld(&world);

	// Set default enemy texture
	enemiesTexture = &getGameWorld().getContext().textures->get(Textures::ID::Enemies);

}