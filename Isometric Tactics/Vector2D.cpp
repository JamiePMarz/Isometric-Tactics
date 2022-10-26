#include "Vector2D.h"

int Vector2D::scaledSize = 1;
int Vector2D::scale = 1;
int Vector2D::mapXOffSet = 0;


Vector2D::Vector2D()
{
	this->zero();
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

//Vector functions, add, subtract, multiple, divide, equal
Vector2D& Vector2D::add(const Vector2D& vector)
{//myVector.add(thisVector)
	this->x += vector.x;
	this->y += vector.y;

	return *this;
}
Vector2D& Vector2D::subtract(const Vector2D& vector)
{
	this->x -= vector.x;
	this->y -= vector.y;

	return *this;
}
Vector2D& Vector2D::multiply(const Vector2D& vector)
{
	this->x *= vector.x;
	this->y *= vector.y;

	return *this;
}
Vector2D& Vector2D::divide(const Vector2D& vector)
{
	this->x /= vector.x;
	this->y /= vector.y;

	return *this;
}
Vector2D& Vector2D::equal(const Vector2D& vector)
{
	this->x = vector.x;
	this->y = vector.y;

	return *this;
}

//overloading +, -, *, /
Vector2D& operator + (Vector2D& v1, const Vector2D& v2)
{//vector1 + vector2 = vector3
	return v1.add(v2);
}
Vector2D& operator - (Vector2D& v1, const Vector2D& v2)
{
	return v1.subtract(v2);
}
Vector2D& operator * (Vector2D& v1, const Vector2D& v2)
{
	return v1.multiply(v2);
}
Vector2D& operator / (Vector2D& v1, const Vector2D& v2)
{
	return v1.divide(v2);
}


//overloading +=, -=, *=, /=, =
Vector2D& Vector2D::operator += (const Vector2D& vector)
{//vector1 += vector2
	return this->add(vector);
}
Vector2D& Vector2D::operator -= (const Vector2D& vector)
{
	return this->subtract(vector);
}
Vector2D& Vector2D::operator *= (const Vector2D& vector)
{
	return this->multiply(vector);
}
Vector2D& Vector2D::operator /= (const Vector2D& vector)
{
	return this->divide(vector);
}
Vector2D& Vector2D::operator = (const Vector2D& vector)
{
	return this->equal(vector);
}

Vector2D& Vector2D::operator * (const int& i)
{//vector *= int
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::zero()
{
	this->x = 0.0f;
	this->y = 0.0f;

	return *this;
}


//overloading <<
std::ostream& operator << (std::ostream& stream, const Vector2D& vector)
{
	stream << "(" << vector.x << "," << vector.y << ")";
	return stream;
}

bool Vector2D::operator == (const Vector2D& vector)
{
	return (x == vector.x && y == vector.y);
}

bool Vector2D::operator != (const Vector2D& vector)
{
	return !(x == vector.x || y == vector.y);
}




void Vector2D::screenFromGrid(Vector2D& screen, Vector2D& grid)
{
	screen.x = (grid.x - grid.y) * (scaledSize / 2) - (scaledSize / 2) + mapXOffSet;
	screen.y = (grid.x + grid.y) * (scaledSize / 4) - (scaledSize / 2);
}

void Vector2D::gridFromScreen(Vector2D& grid, Vector2D& screen)
{
	grid.x = std::round((screen.x / (scaledSize / 2) + screen.y / (scaledSize / 4)) / 2) - 8; //offsets????
	grid.y = std::round((screen.y / (scaledSize / 4) - screen.x / (scaledSize / 2)) / 2) + 7;
}