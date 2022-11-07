#include "TransformComponent.h"


TransformComponent::TransformComponent()
{
	screen.zero();
}

TransformComponent::TransformComponent(int aScale)
{
	screen.zero();
	scale = aScale;
}

TransformComponent::TransformComponent(float x, float y)
{
	screen.x = x;
	screen.y = y;
}

TransformComponent::TransformComponent(int x, int y, int aHeight, int aWidth, int aScale)
{
	grid.x = static_cast<float>(x);
	grid.y = static_cast<float>(y);
	IsometricGrid::screenFromGrid(screen, grid);
	height = aHeight;
	width = aWidth;
	scale = aScale;
}

void TransformComponent::initialize()
{
	velocity.zero();
}

void TransformComponent::update()
{
	screen.x += static_cast<float>(velocity.x * speed);
	screen.y += static_cast<float>(velocity.y * speed);
}

void TransformComponent::moveByGrid(Vector2D& newGrid)
{
	grid.x = newGrid.x;
	grid.y = newGrid.y;
	IsometricGrid::screenFromGrid(screen, grid);
}