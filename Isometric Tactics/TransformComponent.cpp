#include "TransformComponent.h"


TransformComponent::TransformComponent()
{
	screenPos.zero();
}

TransformComponent::TransformComponent(int aScale)
{
	screenPos.zero();
	scale = aScale;
}

TransformComponent::TransformComponent(float x, float y)
{
	screenPos.x = x;
	screenPos.y = y;
}

TransformComponent::TransformComponent(int x, int y, int aHeight, int aWidth, int aScale)
{
	gridPos.x = x;
	gridPos.y = y;
	IsometricGrid::screenFromGrid(screenPos, gridPos);
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
	screenPos.x += static_cast<int>(velocity.x * speed);
	screenPos.y += static_cast<int>(velocity.y * speed);
}

void TransformComponent::moveByGrid(Vector2D& grid)
{
	gridPos.x = grid.x;
	gridPos.y = grid.y;
	IsometricGrid::screenFromGrid(screenPos, gridPos);
}