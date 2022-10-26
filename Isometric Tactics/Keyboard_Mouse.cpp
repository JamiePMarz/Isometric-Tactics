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

void Keyboard_Mouse::gridFromScreen()//move to vector
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
