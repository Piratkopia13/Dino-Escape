#include "Game.h"

int main() {

	// Todo list available at https://trello.com/b/uA7B6Z2j/dino-escape-todo

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.run();

	return 0;
}
