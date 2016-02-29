//#include <Windows.h>

#include "Game.h"

//int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
int main() {

	// Todo list available at https://trello.com/b/uA7B6Z2j/dino-escape-todo

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;

	try {

		game.run();

	} catch (std::exception e) {

		std::cout << e.what() << std::endl;
		system("pause");

	}

	return 0;
}
