#pragma once

#include "Vector2.h"
#include "Vector3.h"

class MathHelper
{
public:
	static float MagnitudeSquared(const Vector2& v);
	static float MagnitudeSquared(const Vector3& v);
	static float Magnitude(const Vector2& v);
	static float Magnitude(const Vector3& v);
	static Vector2 Normalize(const Vector2& v);
	static Vector3 Normalize(const Vector3& v);
	static float Dot(const Vector2& a, const Vector2& b);
	static float Dot(const Vector3& a, const Vector3& b);
	static Vector3 Cross(const Vector3& a, const Vector3& b);

	static float Lerp(const float& a, const float& b, float t);
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	static bool CheckEqual(float a, float b);
	static bool CheckEqual(const Vector2& a, const Vector2& b);
	static bool CheckEqual(const Vector3& a, const Vector3& b);
};

