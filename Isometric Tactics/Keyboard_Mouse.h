#pragma once
#include "Vector2D.h"
#include "IsometricGrid.h"
#include <SDL.h>
#include "Macros.h"


class Keyboard_Mouse
{
public:
	Keyboard_Mouse();
	~Keyboard_Mouse();


	//controls
	static bool hover(Vector2D& vector);

	static bool leftClick();
	static bool rightClick();

	static bool keyPress(SDL_KeyCode key);

	//getters and setters
	void setMouseXY(int& mouseX, int& mouseY);

	static Vector2D& getScreen() { return screen; }
	static Vector2D& getGrid() { return grid; }

	//public vars
	static SDL_Event event;

private:
	static Vector2D screen, grid;
	

};
