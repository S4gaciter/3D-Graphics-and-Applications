#include "CmdSetShading.h"
#include "Rasterizer.h"

bool CmdSetShading::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }
    
    ShadeMode shadeMode = ShadeMode::Gouraud;

    if (params[0] == "flat")
    {
        shadeMode = ShadeMode::Flat;
    }
    else if (params[0] == "gouraud")
    {
        shadeMode = ShadeMode::Gouraud;
    }
    else if (params[0] == "phong")
    {
        shadeMode = ShadeMode::Phong;
    }
    else
    {
        return false;
    }

    return true;
}
