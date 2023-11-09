#include "CmdSetCameraNear.h"
#include "Camera.h"
#include "VariableCache.h"

bool CmdSetCameraNear::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }

    VariableCache* vc = VariableCache::Get();
    float value = vc->GetFloat(params[0]);

    Camera::Get()->SetNearPlane(value);

    return true;
}
