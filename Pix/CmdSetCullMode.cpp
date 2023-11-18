#include "CmdSetCullMode.h"
#include "PrimitivesManager.h"

bool CmdSetCullMode::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }
    CullMode cull;
    if (params[0] == "none")
    {
        cull = CullMode::None;
    }
    else if (params[0] == "back")
    {
        cull = CullMode::Back;
    }
    else if (params[0] == "front")
    {
        cull = CullMode::Front;
    }
    PrimitivesManager::Get()->SetCullMode(cull);
    return true;
}