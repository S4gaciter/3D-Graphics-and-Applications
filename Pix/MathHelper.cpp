#include "MathHelper.h"
#include <math.h>

float MathHelper::MagnitudeSquared(const Vector2& v)
{
	return { v.x * v.x + v.y * v.y };
}

float MathHelper::MagnitudeSquared(const Vector3& v)
{
	return { v.x * v.x + v.y * v.y + v.z * v.z };
}

float MathHelper::Magnitude(const Vector2& v)
{
	return sqrtf(MagnitudeSquared(v));
}

float MathHelper::Magnitude(const Vector3& v)
{
	return sqrtf(MagnitudeSquared(v));
}

Vector2 MathHelper::Normalize(const Vector2& v)
{
	return v / Magnitude(v);
}

Vector3 MathHelper::Normalize(const Vector3& v)
{
	return v / Magnitude(v);
}

float MathHelper::Dot(const Vector2& a, const Vector2& b)
{
	return (a.x * b.x) + (a.y * b.y);
}

float MathHelper::Dot(const Vector3& a, const Vector3& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vector3 MathHelper::Cross(const Vector3& a, const Vector3& b)
{
	return { (a.y * b.z) - (a.z * b.y), 
		     (a.x * b.z) - (a.z * b.x), 
		     (a.x * b.y) - (a.y * b.x)};
}
