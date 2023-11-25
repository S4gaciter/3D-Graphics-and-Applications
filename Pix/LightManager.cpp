#include "LightManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"

LightManager* LightManager::Get()
{
	static LightManager sInstance;
	return &sInstance;
}

void LightManager::OnNewFrame()
{
	mLights.clear();
	mAmbient = X::Colors::White;
	mDiffuse = X::Colors::White;
	mSpecular = X::Colors::White;
}

void LightManager::AddDirectionalLight(const Vector3& direction)
{
	auto light = std::make_unique<DirectionalLight>();
	light->SetDirection(direction);
	light->SetAmbient(mAmbient);
	light->SetDiffuse(mDiffuse);
	light->SetSpecular(mSpecular);
	mLights.emplace_back(std::move(light));
}

void LightManager::AddPointLight(const Vector3& position, float constant, float linear, float quadratic)
{
	auto light = std::make_unique<PointLight>();
	light->SetPosition(position);
	light->SetAttenuation(constant, linear, quadratic);
	light->SetAmbient(mAmbient);
	light->SetDiffuse(mDiffuse);
	light->SetSpecular(mSpecular);
	mLights.emplace_back(std::move(light));
}

void LightManager::SetLightingAmbient(const X::Color& ambient)
{
	mAmbient = ambient;
}

void LightManager::SetLightingDiffuse(const X::Color& diffuse)
{
	mDiffuse = diffuse;
}

void LightManager::SetLightingSpecular(const X::Color& specular)
{
	mSpecular = specular;
}

X::Color LightManager::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
	if (mLights.empty())
	{
		return X::Colors::White;
	}
	
	X::Color color = X::Colors::Black;
	for (auto& light : mLights)
	{
		color += light->ComputeLightColor(position, normal);
	}

	return color;
}
