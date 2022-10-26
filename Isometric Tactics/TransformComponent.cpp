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

TransformComponent::TransformComponent(int x, int y, int aHeight, int aWidth)
{
	gridPos.x = x;
	gridPos.y = y;
	Vector2D::screenFromGrid(screenPos, gridPos);
	height = aHeight;
	width = aWidth;
	scale = Vector2D::scale;
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
	Vector2D::screenFromGrid(screenPos, gridPos);
}
