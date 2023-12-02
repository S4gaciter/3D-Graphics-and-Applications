#include "PointLight.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color PointLight::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
    auto camera = Camera::Get();
    auto mm = MaterialManager::Get();


    Vector3 dirToLight = mPosition - position;
    float distanceToLight = MathHelper::Magnitude(dirToLight);
    dirToLight /= distanceToLight;

    float atten = 1.0f / (mAttenConst + (mAttenLinear * distanceToLight) 
                + (mAttenQuadratic * distanceToLight * distanceToLight));
    float attenValue = X::Math::Clamp(atten, 0.0f, 1.0f);

    X::Color colorAmbient = mAmbient * mm->GetMaterialAmbient() * attenValue;

    float dot = X::Math::Max(MathHelper::Dot(dirToLight, normal), 0.0f);
    X::Color colorDiffuse = mDiffuse * mm->GetMaterialDiffuse() * dot * attenValue;

    Vector3 dirToEye = MathHelper::Normalize(camera->GetPosition() - position);
    Vector3 half = MathHelper::Normalize(dirToLight + dirToEye);
    float fallOff = pow(MathHelper::Dot(half, normal), mm->GetMaterialShininess());
    fallOff = X::Math::Max(fallOff, 0.0f);
    X::Color colorSpecular = mSpecular * mm->GetMaterialSpecular() * fallOff * attenValue;

    return colorAmbient + colorDiffuse + colorSpecular;
}

void PointLight::SetPosition(const Vector3& position)
{
    mPosition = position;
}

void PointLight::SetAttenuation(float constant, float linear, float quadratic)
{
    mAttenConst = constant;
    mAttenLinear = linear;
    mAttenQuadratic = quadratic;
}
