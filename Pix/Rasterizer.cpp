#include "Rasterizer.h"
#include "DepthBuffer.h"
#include "LightManager.h"
#include "TextureCache.h"

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode mode)
{
	mFillMode = mode;
}

void Rasterizer::SetShadeMode(ShadeMode mode)
{
	mShadeMode = mode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	if (DepthBuffer::Get()->CheckDepthBuffer(v.position.x + 0.5f, v.position.y + 0.5, v.position.z))
	{
		mColor = TextureCache::Get()->SampleColor(v.color);
		if (mShadeMode == ShadeMode::Phong)
		{
			mColor *= LightManager::Get()->ComputeLightColor(v.worldPosition, v.worldNormal);
		}
		DrawPoint(v.position.x + 0.5f, v.position.y + 0.5);
	}
}

void Rasterizer::DrawLine(const Vertex& v0, const Vertex& v1)
{
	if (MathHelper::CheckEqual(v0.position, v1.position))
	{
		DrawPoint(v0);
	}
	else
	{
		float dx = v1.position.x - v0.position.x;
		float dy = v1.position.y - v0.position.y;

		// normal slope lerp
		Vertex startV, endV;
		if (std::abs(dy) < std::abs(dx))
		{
			if (v0.position.x < v1.position.x)
			{
				startV = v0;
				endV = v1;
			}
			else
			{
				startV = v1;
				endV = v0;
			}
			for (float x = std::floor(startV.position.x); x <= std::floor(endV.position.x + 0.5f); ++x)
			{
				float t = (x - startV.position.x) / (endV.position.x - startV.position.x);
				Vertex v = LerpVertex(startV, endV, t, mShadeMode == ShadeMode::Phong);
				DrawPoint(v);
			}
		}
		else
		{
			if (v0.position.y < v1.position.y)
			{
				startV = v0;
				endV = v1;
			}
			else
			{
				startV = v1;
				endV = v0;
			}
			for (float y = std::floor(startV.position.y); y <= std::floor(endV.position.y + 0.5f); ++y)
			{
				float t = (y - startV.position.y) / (endV.position.y - startV.position.y);
				Vertex v = LerpVertex(startV, endV, t, mShadeMode == ShadeMode::Phong);
				DrawPoint(v);
			}
		}
	}
}

void Rasterizer::DrawTriangle(Vertex v0, Vertex v1, Vertex v2)
{
	if (mShadeMode == ShadeMode::Flat)
	{
		v1.color = v0.color;
		v2.color = v0.color;
	}
	switch (mFillMode)
	{
	case FillMode::Wireframe:
	{
		DrawLine(v0, v1);
		DrawLine(v1, v2);
		DrawLine(v2, v0);
	}
	break;
	case FillMode::Solid:
	{
		DrawFilledTriangle(v0, v1, v2);
	}
	break;
	}
	
}

void Rasterizer::DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	std::vector<Vertex> sortedVertices = { v0, v1, v2 };
	std::sort(sortedVertices.begin(), sortedVertices.end(),
		[](const Vertex& lhs, const Vertex& rhs)
		{
			return lhs.position.y < rhs.position.y;
		});
	if (MathHelper::CheckEqual(sortedVertices[0].position.y, sortedVertices[1].position.y))
	{
		DrawTopFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	else if (MathHelper::CheckEqual(sortedVertices[1].position.y, sortedVertices[2].position.y))
	{
		DrawBottomFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	else
	{
		float t = (sortedVertices[1].position.y - sortedVertices[0].position.y) / (sortedVertices[2].position.y - sortedVertices[0].position.y);
		Vertex splitVertex = LerpVertex(sortedVertices[0], sortedVertices[2], t, mShadeMode == ShadeMode::Phong);
		// bottom flat
		DrawBottomFilledTriangle(sortedVertices[0], sortedVertices[1], splitVertex);
		// top flat
		DrawTopFilledTriangle(sortedVertices[1], splitVertex, sortedVertices[2]);
	}
}

void Rasterizer::DrawTopFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	Vertex topLeft, topRight;
	if (v0.position.x < v1.position.x)
	{
		topLeft = v0;
		topRight = v1;
	}
	else
	{
		topLeft = v1;
		topRight = v0;
	}

	float dy = v2.position.y - v0.position.y;
	for (float y = v0.position.y; y <= v2.position.y; ++y)
	{
		float t = (y - v0.position.y) / dy;
		Vertex leftVertex = LerpVertex(topLeft, v2, t, mShadeMode == ShadeMode::Phong);
		Vertex rightVertex = LerpVertex(topRight, v2, t, mShadeMode == ShadeMode::Phong);
		DrawLine(leftVertex, rightVertex);
	}
}

void Rasterizer::DrawBottomFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	Vertex bottomLeft, bottomRight;
	if (v0.position.x < v1.position.x)
	{
		bottomLeft = v1;
		bottomRight = v2;
	}
	else
	{
		bottomLeft = v2;
		bottomRight = v1;
	}

	float dy = v2.position.y - v0.position.y;
	for (float y = v0.position.y; y <= v2.position.y; ++y)
	{
		float t = (y - v0.position.y) / dy;
		Vertex leftVertex = LerpVertex(v0, bottomLeft, t, mShadeMode == ShadeMode::Phong);
		Vertex rightVertex = LerpVertex(v0, bottomRight, t, mShadeMode == ShadeMode::Phong);
		DrawLine(leftVertex, rightVertex);
	}
}
