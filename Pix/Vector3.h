#pragma once

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{

	}
	Vector3(float a, float b, float c)
		: x(a)
		, y(b)
		, z(c)
	{

	}

	Vector3 operator-() const { return { -x, -y, -z }; }
		  
	Vector3 operator+(const Vector3& other) const { return { x + other.x, y + other.y, z + other.z }; }
	Vector3 operator-(const Vector3& other) const { return { x - other.x, y - other.y, z - other.z }; }
	Vector3 operator*(float s) const { return { x * s, y * s, z * s }; }
	Vector3 operator/(float s) const { return { x / s, y / s, z / s }; }
		  
	Vector3 operator+=(const Vector3& other) { x += other.x, y += other.y, z += other.z; return *this; }
	Vector3 operator-=(const Vector3& other) { x -= other.x, y -= other.y, z -= other.z; return *this; }
	Vector3 operator*=(float s) { x *= s, y *= s, z *= s; return *this; }
	Vector3 operator/=(float s) { x /= s, y /= s, z /= s; return *this; }
};