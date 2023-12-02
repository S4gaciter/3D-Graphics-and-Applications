#pragma once

#include "MathHelper.h"
#include <XEngine.h>

class Light
{
public:
	virtual ~Light() = default;

	virtual X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const = 0;

	// color without lighting
	void SetAmbient(const X::Color& ambient) { mAmbient = ambient; }
	// color with lighting
	void SetDiffuse(const X::Color& diffuse) { mDiffuse = diffuse; }
	// enhanced color at lighting focal point
	void SetSpecular(const X::Color& specular) { mSpecular = specular; }

protected:
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
};

