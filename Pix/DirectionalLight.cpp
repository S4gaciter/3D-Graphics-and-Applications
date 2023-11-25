#include "DirectionalLight.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color DirectionalLight::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
    auto camera = Camera::Get();
    auto mm = MaterialManager::Get();

    X::Color colorAmbient = mAmbient * mm->GetMaterialAmbient();

    Vector3 dirToLight = -mDirection;
    float dot = X::Math::Max(MathHelper::Dot(dirToLight, normal), 0.0f);
    X::Color colorDiffuse = mDiffuse * mm->GetMaterialDiffuse() * dot;

    Vector3 dirToEye = MathHelper::Normalize(camera->GetPosition() - position);
    Vector3 half = MathHelper::Normalize(dirToLight + dirToEye);
    float fallOff = X::Math::Max(pow(MathHelper::Dot(half, normal), mm->GetMaterialShininess()), 0.0f);
    X::Color colorSpecular = mSpecular * mm->GetMaterialSpecular() * fallOff;

    return colorAmbient + colorDiffuse + colorSpecular;
}

void DirectionalLight::SetDirection(const Vector3& direction)
{
    mDirection = direction;
}
