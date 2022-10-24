#pragma once
#include "Vector2D.h"
#include "IsometricMap.h"



class Keyboard_Mouse
{
public:
	Keyboard_Mouse();
	~Keyboard_Mouse();


	static bool mouseHovers(Vector2D& vector);

	static bool leftClick();
	static bool rightClick();



	//getters and setters
	Vector2D getScreenPos() { return screenPos; }
	void setMouseXY(int& mouseX, int& mouseY);

	static Vector2D& getGridPos() { return gridPos; }


	void gridFromScreen();
	static void screenFromGrid(Vector2D& screen, Vector2D& grid);
	static void gridFromScreen(Vector2D& grid, Vector2D& screen);

	
private:
	static Vector2D screenPos, gridPos;

};
