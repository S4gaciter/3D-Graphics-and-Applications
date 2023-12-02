#include "SpotLight.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color SpotLight::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
    auto camera = Camera::Get();
    auto mm = MaterialManager::Get();


    Vector3 dirToLight = mPosition - position;
    float distanceToLight = MathHelper::Magnitude(dirToLight);
    dirToLight /= distanceToLight;

    Vector3 lightDir = -dirToLight;
    float dirDot = MathHelper::Dot(lightDir, mDirection);
    if (dirDot < mCosAngle)
    {
        return 0.0f;
    }

    float spot = std::pow(dirDot, mDecay);
    float atten = spot / (mAttenConst + (mAttenLinear * distanceToLight)
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

void SpotLight::SetPosition(const Vector3& position)
{
    mPosition = position;
}

void SpotLight::SetDirection(const Vector3& direction)
{
    mDirection = direction;
}

void SpotLight::SetAttenuation(float constant, float linear, float quadratic)
{
    mAttenConst = constant;
    mAttenLinear = linear;
    mAttenQuadratic = quadratic;
}

void SpotLight::SetAngle(float angle)
{
    mCosAngle = std::cos(angle);
}

void SpotLight::SetDecay(float decay)
{
    mDecay = decay;
}
