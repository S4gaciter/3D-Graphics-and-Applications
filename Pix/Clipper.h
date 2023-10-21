#pragma once

#include "Vertex.h"

class Clipper
{
public:
	static Clipper* Get();

	~Clipper();
	void OnNewFrame();

	// return true if clip test passes
	bool ClipPoint(const Vertex& v);
	bool ClipLine(Vertex& v0, Vertex& v1);
	bool ClipTriangle(std::vector<Vertex>& vertices);

	bool IsClipping() const { return mIsClipping; }
	void SetClipping(bool clip) { mIsClipping = clip; }
private:
	Clipper();
	bool mIsClipping = false;
};

