#include "Keyboard_Mouse.h"

Vector2D Keyboard_Mouse::screenPos;
Vector2D Keyboard_Mouse::gridPos;


Keyboard_Mouse::Keyboard_Mouse()
{}
Keyboard_Mouse::~Keyboard_Mouse()
{}


void Keyboard_Mouse::setMouseXY(int& mouseX, int& mouseY)
{
	screenPos.x = mouseX;
	screenPos.y = mouseY;
	Vector2D::gridFromScreen(gridPos, screenPos);
}


bool Keyboard_Mouse::leftClick()
{
	if (Game::event.button.button == SDL_BUTTON_LEFT)//add no repeat?
		return  true;
	else
		return false;
}

bool Keyboard_Mouse::rightClick()
{
	if (Game::event.button.button == SDL_BUTTON_RIGHT)
		return  true;
	else
		return false;
}

bool Keyboard_Mouse::hover(Vector2D& vector)
{
	if (vector == gridPos || vector == screenPos)
		return true;
	else
		return false;
}

bool Keyboard_Mouse::keyPressed(SDL_KeyCode key)
{
	if (Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == key && Game::event.key.repeat == 0)
		return  true;
	else
		return false;
}
