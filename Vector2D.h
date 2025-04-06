#pragma once

#include <iostream>

class Vector2D
{

public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Zero();

	Vector2D& Add(const Vector2D& vec2D);
	Vector2D& Subtract(const Vector2D& vec2D);
	Vector2D& Multiply(const Vector2D& vec2D);
	Vector2D& Divide(const Vector2D& vec2D);

	Vector2D& Multiply(const float& num);
	Vector2D& Divide(const float& num);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	friend Vector2D& operator*(Vector2D& v1, const float& num);
	friend Vector2D& operator/(Vector2D& v1, const float& num);

	Vector2D& operator+=(const Vector2D& vec2D);
	Vector2D& operator-=(const Vector2D& vec2D);
	Vector2D& operator*=(const Vector2D& vec2D);
	Vector2D& operator/=(const Vector2D& vec2D);

	Vector2D& operator*=(const float& num);
	Vector2D& operator/=(const float& num);

	Vector2D& operator-();

	friend std::ostream& operator<<(std::ostream& out_stream, const Vector2D vec);
	friend std::istream& operator>>(std::istream& in_stream, Vector2D vec);
};

