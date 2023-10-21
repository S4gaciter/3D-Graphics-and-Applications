#pragma once

#include <XEngine.h>
#include "PrimitivesManager.h"

enum class FillMode
{
	Solid,
	Wireframe
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode mode);

	void DrawPoint(int x, int y);

	void DrawPoint(const Vertex& v);
	void DrawLine(const Vertex& v0, const Vertex& v1);
	void DrawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
private:
	void DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
};