#pragma once

#include "Vertex.h"

enum class Topology
{
	Point,
	Line,
	Triangle
};

enum class CullMode
{
	None, // don't cull anything
	Back, // cull anything facing away from the camera
	Front // cull anything facing the camera
};

class PrimitivesManager
{
public:
	~PrimitivesManager();

	static PrimitivesManager* Get();

	void OnNewFrame();
	void SetCullMode(CullMode mode);

	bool BeginDraw(Topology topology, bool applyTransform = false);
	void AddVertex(const Vertex& vertex);
	bool EndDraw();

private:
	PrimitivesManager();

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	CullMode mCullMode = CullMode::Back;
	bool mDrawBegin = false;
	bool mApplyTransform = false;
};
