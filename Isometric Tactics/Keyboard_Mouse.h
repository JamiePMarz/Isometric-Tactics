#pragma once
#include "Vector2D.h"
#include "IsometricMap.h"
#include "SDL.h"



class Keyboard_Mouse
{
public:
	Keyboard_Mouse();
	~Keyboard_Mouse();


	//controls
	static bool hover(Vector2D& vector);

	static bool leftClick();
	static bool rightClick();

	static bool keyPressed(SDL_KeyCode key);




	//getters and setters
	void setMouseXY(int& mouseX, int& mouseY);

	Vector2D getScreenPos() { return screenPos; }
	static Vector2D& getGridPos() { return gridPos; }

	
private:
	static Vector2D screenPos, gridPos;

};
