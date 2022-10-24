#include "WindowManager.h"


WindowManager::WindowManager()
{}
WindowManager::~WindowManager()
{}

void WindowManager::initialize(const char* windowTitle, int xpos, int ypos, int width, int height, bool isFullscreen)
{
	fullscreen = isFullscreen;


	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised..." << std::endl;
		window = SDL_CreateWindow(windowTitle, xpos, ypos, width, height, fullscreen);
		windowHeight = height;
		windowWidth = width;

		if (window)
			std::cout << "Window Created..." << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		std::cout << "Renderer Created..." << std::endl;
		initialized = true;
	}
	else
		initialized = false;
}

void WindowManager::windowClean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Window Cleaned :)" << std::endl;
}