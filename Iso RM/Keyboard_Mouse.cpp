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
	gridFromScreen();
}

void Keyboard_Mouse::gridFromScreen()
{
	int scale = IsometricMap::getScaledSize();
	gridPos.x = std::round((screenPos.x / (scale / 2) + screenPos.y / (scale / 4)) / 2) - 8; //offsets????
	gridPos.y = std::round((screenPos.y / (scale / 4) - screenPos.x / (scale / 2)) / 2) + 7;
}


void Keyboard_Mouse::screenFromGrid(Vector2D& screen, Vector2D& grid)
{
	int scale = IsometricMap::getScaledSize();
	screen.x = (grid.x - grid.y) * (scale / 2) - (scale / 2) + IsometricMap::getXOffSet();
	screen.y = (grid.x + grid.y) * (scale / 4) - (scale / 2);
}

void Keyboard_Mouse::gridFromScreen(Vector2D& grid, Vector2D& screen)
{
	int scale = IsometricMap::getScaledSize();
	grid.x = std::round((screen.x / (scale / 2) + screen.y / (scale / 4)) / 2) - 8; //offsets????
	grid.y = std::round((screen.y / (scale / 4) - screen.x / (scale / 2)) / 2) + 7;
}


bool Keyboard_Mouse::leftClick()
{
	if (Game::event.button.button == SDL_BUTTON_LEFT)
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

bool Keyboard_Mouse::mouseHovers(Vector2D& vector)
{
	if (vector == gridPos || vector == screenPos)
		return true;
	else
		return false;
}

bool Keyboard_Mouse::_1click()
{
	if (Game::event.key.keysym.sym == SDLK_1)
		return  true;
	else
		return false;
}

bool Keyboard_Mouse::_2click()
{
	if (Game::event.key.keysym.sym == SDLK_2)
		return  true;
	else
		return false;
}

bool Keyboard_Mouse::_3click()
{
	if (Game::event.key.keysym.sym == SDLK_3)
		return  true;
	else
		return false;
}

bool Keyboard_Mouse::_4click()
{
	if (Game::event.key.keysym.sym == SDLK_4)
		return  true;
	else
		return false;
}