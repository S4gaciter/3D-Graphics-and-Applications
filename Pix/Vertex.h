#pragma once

#include "MathHelper.h"
#include <XEngine.h>

struct Vertex
{
    Vector3 position;
    Vector3 normal;
    Vector3 worldPosition;
    Vector3 worldNormal;
    X::Color color;
};

inline static Vector3 LerpPosition(const Vector3& a, const Vector3& b, float t)
{
    return MathHelper::Lerp(a, b, t);
}

inline static Vector3 LerpNormal(const Vector3& a, const Vector3& b, float t)
{
    return MathHelper::Normalize(MathHelper::Lerp(a, b, t));
}

inline static X::Color LerpColor(const X::Color& a, const X::Color& b, float t)
{
    return {
        MathHelper::Lerp(a.r, b.r, t),
        MathHelper::Lerp(a.g, b.g, t),
        MathHelper::Lerp(a.b, b.b, t),
        MathHelper::Lerp(a.a, b.a, t)
    };
}

inline static Vertex LerpVertex(const Vertex& a, const Vertex& b, float t, bool lerpNormal = false)
{
    Vertex ret;
    ret.position = LerpPosition(a.position, b.position, t);
    ret.worldPosition = LerpPosition(a.worldPosition, b.worldPosition, t);
    if (lerpNormal)
    {
        ret.normal = LerpNormal(a.normal, b.normal, t);
        ret.worldNormal = LerpNormal(a.worldNormal, b.worldNormal, t);
    }
    ret.color = LerpColor(a.color, b.color, t);
    return ret;
}