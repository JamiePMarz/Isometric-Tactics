#include <iostream>
#include "Game.h"

Game* game = nullptr;


int main(int argc, char* argv[])
{

	game = new Game();
	game->initialize();

	Uint32 frameStart;
	int frameTime;
	int FPS = 60;
	int frameDelay = 1000 / FPS;


	while (game->isRunning())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		//std::cout << frameTime << std::endl;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);

	}

	game->clean();

	//std::cin.get();
	return 0;
}