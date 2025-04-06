#include "Vector2D.h"


Vector2D::Vector2D()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::Zero()
{
	this->x = this->y = 0;
	return *this;
}

Vector2D& Vector2D::Add(const Vector2D& vec2D)
{
	this->x += vec2D.x;
	this->y += vec2D.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec2D)
{
	this->x -= vec2D.x;
	this->y -= vec2D.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec2D)
{
	this->x *= vec2D.x;
	this->y *= vec2D.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec2D)
{
	this->x /= vec2D.x;
	this->y /= vec2D.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const float& num)
{
	this->x *= num;
	this->y *= num;

	return *this;
}

Vector2D& Vector2D::Divide(const float& num)
{
	this->x /= num;
	this->y /= num;

	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec2D)
{
	return this->Add(vec2D);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec2D)
{
	return this->Subtract(vec2D);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec2D)
{
	return this->Multiply(vec2D);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec2D)
{
	return this->Divide(vec2D);
}

Vector2D& Vector2D::operator*=(const float& num)
{
	return this->Multiply(num);
}

Vector2D& Vector2D::operator/=(const float& num)
{
	return this->Divide(num);
}

Vector2D& Vector2D::operator-()
{
	this->x = -this->x;
	this->y = -this->y;

	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}

Vector2D& operator*(Vector2D& v1, const float& num)
{
	return v1.Multiply(num);
}

Vector2D& operator/(Vector2D& v1, const float& num)
{
	return v1.Divide(num);
}

std::ostream& operator<<(std::ostream& out_stream, const Vector2D vec)
{
	out_stream << "(" << vec.x << ", " << vec.y << ")";
	return out_stream;
}

std::istream& operator>>(std::istream& in_stream, Vector2D vec)
{
	return (in_stream >> vec.x >> vec.y);
}
