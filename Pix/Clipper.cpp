#include "Clipper.h"
#include "Viewport.h"
#include "Rasterizer.h"

const int BIT_INSIDE    = 0;
const int BIT_LEFT      = 1 << 1; // 0001
const int BIT_RIGHT     = 1 << 2; // 0010
const int BIT_BOTTOM    = 1 << 3; // 0100
const int BIT_TOP       = 1 << 4; // 1000

float minX;
float minY;
float maxX;
float maxY;

Clipper* Clipper::Get()
{
    static Clipper sInstance;
    return &sInstance;
}

Clipper::Clipper()
{
}

Clipper::~Clipper()
{
}

void Clipper::OnNewFrame()
{
    mIsClipping = false;
}

bool Clipper::ClipPoint(const Vertex& v)
{
    if (!mIsClipping)
    {
        return true;
    }

    GetViewportLimits();

    return v.position.x >= minX && v.position.x <= maxX
        && v.position.y >= minY && v.position.y <= maxY;
}

bool Clipper::ClipLine(Vertex& v0, Vertex& v1)
{
    if (!mIsClipping)
    {
        return true;
    }

    GetViewportLimits();

    int cv0 = GetOutputCode(v0);
    int cv1 = GetOutputCode(v1);
    bool accept = false;

    while (!accept)
    {
        // if cv0 and cv1 are inside
        if ((cv0 | cv1) == BIT_INSIDE)
        {
            accept = true;
            break;
        }
        // if cv0 and cv1 are both outside
        else if ((cv0 & cv1) > 0)
        {
            accept = false;
            break;
        }
        // the line crosses through the viewport at some point
        else
        {
            float t = 0.0f;
            int outCodeActive = cv1 > cv0 ? cv1 : cv0;
            if ((outCodeActive & BIT_TOP) > 0)
            {
                t = (minY - v0.position.y) / (v1.position.y - v0.position.y);
            }
            else if ((outCodeActive & BIT_BOTTOM) > 0)
            {
                t = (maxY - v0.position.y) / (v1.position.y - v0.position.y);
            }
            else if ((outCodeActive & BIT_RIGHT) > 0)
            {
                t = (maxX - v0.position.x) / (v1.position.x - v0.position.x);
            }
            else if ((outCodeActive & BIT_LEFT) > 0)
            {
                t = (minX - v0.position.x) / (v1.position.x - v0.position.x);
            }

            if (outCodeActive == cv0)
            {
                v0 = LerpVertex(v0, v1, t);
                cv0 = GetOutputCode(v0.position.x, v0.position.y);
            }
            else
            {
                v1 = LerpVertex(v0, v1, t);
                cv1 = GetOutputCode(v1.position.x, v1.position.y);
            }
        }
    }

    return accept;
}

bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
    if (!mIsClipping)
    {
        return true;
    }

    std::vector<Vertex> newVertices;
    for (int i = 0; i < (int)ClipEdge::Count; ++i)
    {
        newVertices.clear();
        ClipEdge edge = (ClipEdge)i;
        for (size_t n = 0; n < vertices.size(); ++n)
        {
            size_t np1 = (n + 1) % vertices.size();
            const Vertex& v0 = vertices[n];
            const Vertex& v1 = vertices[np1];
            bool isInFrontV0 = IsInFront(edge, v0.position);
            bool isInFrontV1 = IsInFront(edge, v1.position);

            if (isInFrontV0 && isInFrontV1)
            {
                newVertices.push_back(v1);
            }
            else if (isInFrontV0 && !isInFrontV1)
            {
                newVertices.push_back(ComputeIntersection(edge, v0, v1));
            }
            else if (!isInFrontV0 && !isInFrontV1)
            {
                // save nothing
            }
            else if (!isInFrontV0 && isInFrontV1)
            {
                newVertices.push_back(ComputeIntersection(edge, v0, v1));
                newVertices.push_back(v1);
            }
        }
        vertices = newVertices;
    }
    return vertices.size() > 0;
}

bool Clipper::IsInFront(ClipEdge edge, const Vector3& pos)
{
    GetViewportLimits();

    switch (edge)
    {
    case ClipEdge::Left: return pos.x > minX;
    case ClipEdge::Bottom: return pos.y < maxY;
    case ClipEdge::Right: return pos.x < maxX;
    case ClipEdge::Top: return pos.y > minY;
    default:
        break;
    }

    return false;
}

Vertex Clipper::ComputeIntersection(Clipper::ClipEdge edge, const Vertex& v0, const Vertex& v1)
{
    Clipper::GetViewportLimits();

    float t = 0.0f;
    switch (edge)
    {
    case Clipper::ClipEdge::Left:   t = (minX - v0.position.x) / (v1.position.x - v0.position.x); break;
    case Clipper::ClipEdge::Bottom: t = (maxY - v0.position.y) / (v1.position.y - v0.position.y); break;
    case Clipper::ClipEdge::Right:  t = (maxX - v0.position.x) / (v1.position.x - v0.position.x); break;
    case Clipper::ClipEdge::Top:    t = (minY - v0.position.y) / (v1.position.y - v0.position.y); break;
    default:
        break;
    }

    bool isPhong = Rasterizer::Get()->GetShadeMode() == ShadeMode::Phong;
    return LerpVertex(v0, v1, t, isPhong);
}

int Clipper::GetOutputCode(float x, float y)
{
    int code = BIT_INSIDE;
    if (x < Viewport::Get()->GetMinX())
    {
        code |= BIT_LEFT; // 0000 | 0001 = 0001
    }
    else if (x > Viewport::Get()->GetMaxX())
    {
        code |= BIT_RIGHT; // 0000 | 0010 = 0010
    }
    if (y < Viewport::Get()->GetMinY())
    {
        code |= BIT_TOP; // 0000 | 1000 = 1000
    }
    else if (y > Viewport::Get()->GetMaxY())
    {
        code |= BIT_BOTTOM; // 0000 | 0100 = 0100
    }

    return code;
}

int Clipper::GetOutputCode(Vertex v)
{
    return GetOutputCode(v.position.x, v.position.y);
}

void Clipper::GetViewportLimits()
{
    minX = Viewport::Get()->GetMinX();
    minY = Viewport::Get()->GetMinY();
    maxX = Viewport::Get()->GetMaxX();
    maxY = Viewport::Get()->GetMaxY();
}