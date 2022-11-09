#pragma once
#include "SDL.h"
#include <iostream>



class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	void initialize(const char* windowTitle, int xpos, int ypos, int width, int height, bool isFullscreen);

	void windowClean();

	//getters and setters
	bool getInitialized() const { return initialized; }

	int getHeight() const { return windowHeight; }
	int getWidth() const { return windowWidth; }

	SDL_Window* getWindow() const { return window; }

	//public vars
	static SDL_Renderer* renderer;

private:
	bool fullscreen;
	SDL_Window* window;
	int windowWidth;
	int windowHeight;
	
	bool initialized;

};