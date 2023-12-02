#pragma once

#include <XEngine.h>
#include "PrimitivesManager.h"

enum class FillMode
{
	Solid,
	Wireframe
};

enum class ShadeMode
{
	Flat,
	Gouraud,
	Phong
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode mode);
	void SetShadeMode(ShadeMode mode);
	ShadeMode GetShadeMode() { return mShadeMode; }

	void DrawPoint(int x, int y);

	void DrawPoint(const Vertex& v);
	void DrawLine(const Vertex& v0, const Vertex& v1);
	void DrawTriangle(Vertex v0, Vertex v1, Vertex v2);
private:
	void DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void DrawTopFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void DrawBottomFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
	ShadeMode mShadeMode = ShadeMode::Flat;
};