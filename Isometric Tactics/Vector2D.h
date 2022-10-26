#pragma once
#include <iostream>


class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);

	Vector2D& add(const Vector2D& vector);
	Vector2D& subtract(const Vector2D& vector);
	Vector2D& multiply(const Vector2D& vector);
	Vector2D& divide(const Vector2D& vector);
	Vector2D& equal(const Vector2D& vector);

	friend Vector2D& operator + (Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator - (Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator * (Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator / (Vector2D& v1, const Vector2D& v2);

	Vector2D& operator += (const Vector2D& vector);
	Vector2D& operator -= (const Vector2D& vector);
	Vector2D& operator *= (const Vector2D& vector);
	Vector2D& operator /= (const Vector2D& vector);
	Vector2D& operator = (const Vector2D& vector);

	Vector2D& operator * (const int& i);

	Vector2D& zero();

	friend std::ostream& operator << (std::ostream& stream, const Vector2D& vector);

	bool operator == (const Vector2D& vector);
	bool operator != (const Vector2D& vector);

	static void screenFromGrid(Vector2D& screen, Vector2D& grid);
	static void gridFromScreen(Vector2D& grid, Vector2D& screen);

	//public vars
	float x;
	float y;

	static int scaledSize;
	static int scale;
	static int mapXOffSet;

private:

};