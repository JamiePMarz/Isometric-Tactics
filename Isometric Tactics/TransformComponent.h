#pragma once
#include "Components.h"
#include "Vector2D.h"
#include "Keyboard_Mouse.h"
#include "IsometricGrid.h"


class TransformComponent : public Component
{
public:

	TransformComponent();
	TransformComponent(int aScale);
	TransformComponent(float x, float y);
	TransformComponent(int x, int y, int aHeight, int aWidth, int aScale);

	void initialize() override;
	void update() override;

	void moveByGrid(Vector2D& newGrid);


	//getters and setters

	//public vars
	Vector2D screen, grid;
	Vector2D velocity;
	int height = 32;
	int width = 32;
	int scale = 2;
	int speed = 4;
	Entity* tile;

private:
	

};