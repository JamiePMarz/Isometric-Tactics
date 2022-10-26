#include "Vector2D.h"


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