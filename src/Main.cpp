#include "Game.h"

int main() {

	// TODO: add some music from https://soundcloud.com/trevor-d-lentz / http://opengameart.org/users/trevor-lentz
	// Add sounds for jumping, shooting, getting hurt, hurting monsters, etc
	// DONE - Interpolate camera
	// DONE - Stick camera view to map borders
	// DONE - Bullet system
	// DONE - Spawn enemies from points on map
	// DONE - Player spawn and finish locations defined on map
	// File for settings level order
	// Enemy AI
	//		DONE - Blobbers, move left and right on platforms
	//		DONE - Effies, shoot fireballs when player is in line of sight
	// DONE - Add debug thing for statically adding shapes for rendering
	// Create resource caching, requesting system
	// Fix jumping
	// Allow multiple tilesets and layers with rendering on top of player, etc
	// TileMap culling outside camera
	// DONE - Fix collisionTiles for entity outside map checking all tiles on the map
	// Switch to strongly typed enumerations

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.run();

	return 0;
}