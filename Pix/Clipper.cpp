#include "Clipper.h"
#include "Viewport.h"

Clipper* Clipper::Get()
{
    static Clipper sInstance;
    return &sInstance;
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
    return false;
}

bool Clipper::ClipLine(Vertex& v0, Vertex& v1)
{
    if (!mIsClipping)
    {
        return true;
    }
    return false;
}

bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
    if (!mIsClipping)
    {
        return true;
    }
    return false;
}

Clipper::Clipper()
{
}
