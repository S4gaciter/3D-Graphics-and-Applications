#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"
#include "LightManager.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		const float hw = gResolutionX * 0.5f;
		const float hh = gResolutionY * 0.5f;
		return Matrix4(
			  hw, 0.0f, 0.0f, 0.0f,
			0.0f,  -hh, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			  hw,   hh, 0.0f, 1.0f
		);
	}

	Vector3 GetFacingNormal(const Vector3& a, const Vector3& b, const Vector3& c)
	{
		const Vector3 v0 = b - a;
		const Vector3 v1 = c - a;
		return MathHelper::Cross(v0, v1);
	}

	bool DrawTriangle(CullMode mode, const Vector3& a, const Vector3& b, const Vector3& c)
	{
		if (mode == CullMode::None)
		{
			return true;
		}

		Vector3 facingNormal = GetFacingNormal(a, b, c);

		switch (mode)
		{
		case CullMode::Back: return facingNormal.z <= 0.0f;
		break;

		case CullMode::Front: return facingNormal.z >= 0.0f;
		break;

		default:
			break;
		}
		return true;
	}
}

PrimitivesManager::PrimitivesManager()
{

}

PrimitivesManager::~PrimitivesManager()
{

}

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}

void PrimitivesManager::OnNewFrame()
{
	mCullMode = CullMode::Back;
	mCorrectUV = false;
}

void PrimitivesManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
}

void PrimitivesManager::SetCorrectUV(bool correct)
{
	mCorrectUV = correct;
}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
	mDrawBegin = true;
	mApplyTransform = applyTransform;
	mTopology = topology;
	mVertexBuffer.clear();
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& vertex)
{
	mVertexBuffer.push_back(vertex);
}

bool PrimitivesManager::EndDraw()
{
	if (!mDrawBegin)
	{
		return false;
	}
	
	switch (mTopology)
	{
	case Topology::Point:
	{
		for (size_t i = 0; i < mVertexBuffer.size(); ++i)
		{
			if (Clipper::Get()->ClipPoint(mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
			}
		}
		return true;
	}
	break;

	case Topology::Line:
	{
		for (size_t i = 1; i < mVertexBuffer.size(); i += 2)
		{
			if (Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
			}
		}
		return true;
	}
	break;

	case Topology::Triangle:
	{
		// world space
        const Matrix4 matWorld = MatrixStack::Get()->GetTransform();
		// viewport space
		const Matrix4 matView = Camera::Get()->GetViewMatrix();
		// camera projection space
		const Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
		// screen space
		const Matrix4 matScreen = GetScreenTransform();
		// normalized device coordinate, or NDC space
		const Matrix4 matNDC = matView * matProj;

		for (size_t i = 2; i < mVertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle = { mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i] };
			if (mApplyTransform)
			{
				if (MathHelper::CheckEqual(MathHelper::MagnitudeSquared(triangle[0].normal), 0.0f))
				{
					Vector3 facingNormal = GetFacingNormal(triangle[0].position,
								     triangle[1].position, triangle[2].position);
					for (size_t t = 0; t < triangle.size(); ++t)
					{
						triangle[t].normal = facingNormal;
					}
				}

				// move to world space
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					triangle[t].position = MathHelper::TransformCoord(triangle[t].position, matWorld);
					triangle[t].normal = MathHelper::TransformNormal(triangle[t].normal, matWorld);
					triangle[t].worldPosition = triangle[t].position;
					triangle[t].worldNormal = triangle[t].normal;
				}
				if (triangle[0].color.z < 0.0f)
				{
					if (mCorrectUV)
					{
						for (size_t t = 0; t < triangle.size(); ++t)
						{
							Vertex& v = triangle[t];
							Vector3 viewPos = MathHelper::TransformCoord(triangle[t].worldPosition, matView);
							v.color.x /= viewPos.z;
							v.color.y /= viewPos.z;
							v.color.w = 1.0f / viewPos.z;
						}
					}
				}
				else if (Rasterizer::Get()->GetShadeMode() != ShadeMode::Phong)
				{
					// calculate lighting
					LightManager* lm = LightManager::Get();
					for (size_t t = 0; t < triangle.size(); ++t)
					{
						Vertex& v = triangle[t];
						v.color *= lm->ComputeLightColor(v.worldPosition, v.worldNormal);
					}
				}

				// move to NDC space
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					triangle[t].position = MathHelper::TransformCoord(triangle[t].position, matNDC);
				}
				if (!DrawTriangle(mCullMode, triangle[0].position, 
					triangle[1].position, triangle[2].position))
				{
					continue;
				}
				// move to screen space
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					triangle[t].position = MathHelper::TransformCoord(triangle[t].position, matScreen);
				}
			}
			if (Clipper::Get()->ClipTriangle(triangle))
			{
				for (size_t t = 2; t < triangle.size(); ++t)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);
				}
			}
		}
		return true;
	}
	break;

	default:
		return false;
	}
}
