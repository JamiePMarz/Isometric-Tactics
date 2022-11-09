#include "Keyboard_Mouse.h"

Vector2D Keyboard_Mouse::screen;
Vector2D Keyboard_Mouse::grid;
SDL_Event Keyboard_Mouse::event;


Keyboard_Mouse::Keyboard_Mouse()
{}
Keyboard_Mouse::~Keyboard_Mouse()
{}


void Keyboard_Mouse::setMouseXY(int& mouseX, int& mouseY)
{
	screen.x = mouseX;
	screen.y = mouseY;
	IsometricGrid::gridFromScreen(grid, screen);
	//LOG(screen);
}


bool Keyboard_Mouse::leftClick()
{
	if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED)
	{
		//LOG("left mb pressed");
		return  true;
	}
	else
		return false;
}

bool Keyboard_Mouse::rightClick()
{
	if (event.button.button == SDL_BUTTON_RIGHT && event.button.state == SDL_PRESSED)
	{
		//LOG(right mb pressed);
		return  true;
	}
	else
		return false;
}

bool Keyboard_Mouse::hover(Vector2D& vector)
{
	if (vector == grid || vector == screen)
		return true;
	else
		return false;
}

bool Keyboard_Mouse::keyPress(SDL_KeyCode key)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == key && event.key.repeat == 0)
		return  true;
	else
		return false;
}
