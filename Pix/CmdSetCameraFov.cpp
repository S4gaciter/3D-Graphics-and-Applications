#include "CmdSetCameraFov.h"
#include "Camera.h"
#include "VariableCache.h"

bool CmdSetCameraFov::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }

    VariableCache* vc = VariableCache::Get();
    float value = vc->GetFloat(params[0]);

    Camera::Get()->SetFOV(value * 3.1416 / 180.0f);

    return true;
}
