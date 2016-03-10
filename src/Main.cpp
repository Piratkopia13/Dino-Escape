#include <Windows.h>

#include "Game.h"

//int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) { // For released version, hides the console
int main() {

	// Todo list available at https://trello.com/b/uA7B6Z2j/dino-escape-todo

	// Check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Create an instance of the game
	Game game;

	try {

		// Run the game, catch any exceptions that makes it here
		game.run();

	} catch (std::exception e) {

		std::cout << "ERROR CATCHED:" << std::endl << e.what() << std::endl;
		system("pause");

	}

	return 0;
}
