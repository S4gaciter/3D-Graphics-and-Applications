#pragma once

#include <XEngine.h>

class MaterialManager
{
public:
	static MaterialManager* Get();

	void OnNewFrame();

	void SetMaterialAmbient(const X::Color& ambient);
	void SetMaterialDiffuse(const X::Color& diffuse);
	void SetMaterialSpecular(const X::Color& specular);
	void SetMaterialShininess(float shininess);

	const X::Color GetMaterialAmbient() const;
	const X::Color GetMaterialDiffuse() const;
	const X::Color GetMaterialSpecular() const;
	float GetMaterialShininess() const;

private:
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
	float mShininess = 1.0f;
};

