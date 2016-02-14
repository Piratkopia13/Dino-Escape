#include "Game.h"

int main() {

	// TODO: add some music from https://soundcloud.com/trevor-d-lentz / http://opengameart.org/users/trevor-lentz
	// Add sounds for jumping, shooting, getting hurt, hurting monsters, etc
	// File for settings level order
	// Create resource caching, requesting system
	// Fix jumping
	// Allow multiple tilesets and layers with rendering on top of player, etc
	// TileMap culling outside camera
	// Switch to strongly typed enumerations
	// Fix glitchy lines on map, especially visible when running on my laptop
	// Add menus / states


	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.run();

	return 0;
}

// DONE - Interpolate camera
// DONE - Stick camera view to map borders
// DONE - Bullet system
// DONE - Spawn enemies from points on map
// DONE - Add debug thing for statically adding shapes for rendering
// DONE - Player spawn and finish locations defined on map
// Enemy AI
//		DONE - Blobbers, move left and right on platforms
//		DONE - Effies, shoot fireballs when player is in line of sight
// DONE - Fix collisionTiles for entity outside map checking all tiles on the map
