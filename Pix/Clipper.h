#pragma once

#include "Vertex.h"

class Clipper
{
public:
	static Clipper* Get();

	~Clipper();
	void OnNewFrame();

	enum class ClipEdge : int
	{
		Left,
		Bottom,
		Right,
		Top,
		Count
	};

	// return true if clip test passes
	bool ClipPoint(const Vertex& v);
	bool ClipLine(Vertex& v0, Vertex& v1);
	bool ClipTriangle(std::vector<Vertex>& vertices);

	bool IsClipping() const { return mIsClipping; }
	void SetClipping(bool clip) { mIsClipping = clip; }
private:
	Clipper();

	int GetOutputCode(float x, float y);
	int GetOutputCode(Vertex v);
	bool IsInFront(ClipEdge edge, const Vector3& pos);
	Vertex ComputeIntersection(Clipper::ClipEdge edge, const Vertex& v0, const Vertex& v1);
	static void GetViewportLimits();

	bool mIsClipping = false;
};

