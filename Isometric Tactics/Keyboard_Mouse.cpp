#include "Keyboard_Mouse.h"

Vector2D Keyboard_Mouse::screenPos;
Vector2D Keyboard_Mouse::gridPos;
SDL_Rect Keyboard_Mouse::dest;


Keyboard_Mouse::Keyboard_Mouse()
{}
Keyboard_Mouse::~Keyboard_Mouse()
{}


void Keyboard_Mouse::setMouseXY(int& mouseX, int& mouseY)
{
	screenPos.x = mouseX;
	screenPos.y = mouseY;
	dest.x = mouseX;//????
	dest.y = mouseY;
	dest.w = dest.h = 96;
	IsometricGrid::gridFromScreen(gridPos, screenPos);
	//std::cout << screenPos << std::endl;
}


bool Keyboard_Mouse::leftClick()
{
	if (Game::event.button.button == SDL_BUTTON_LEFT && Game::event.button.state == SDL_PRESSED)
	{
		//std::cout << "lmb clicked\n";
		return  true;
	}
	else
		return false;
}

bool Keyboard_Mouse::rightClick()
{
	if (Game::event.button.button == SDL_BUTTON_RIGHT && Game::event.button.state == SDL_PRESSED)
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
