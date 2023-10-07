#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}
	Vector2(float a, float b)
		: x(a)
		, y(b)
	{

	}

	Vector2 operator-() const { return { -x, -y }; }

	Vector2 operator+(const Vector2& other) { return { x + other.x, y + other.y }; }
	Vector2 operator-(const Vector2& other) { return { x - other.x, y - other.y }; }
	Vector2 operator*(float s) const { return { x * s, y * s }; }
	Vector2 operator/(float s) const { return { x / s, y / s }; }

	Vector2 operator+=(const Vector2& other) { x += other.x, y += other.y; return *this; }
	Vector2 operator-=(const Vector2& other) { x -= other.x, y -= other.y; return *this; }
	Vector2 operator*=(float s) { x *= s, y *= s; return *this; }
	Vector2 operator/=(float s) { x /= s, y /= s; return *this; }
};