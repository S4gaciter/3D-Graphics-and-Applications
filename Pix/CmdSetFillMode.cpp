#include "CmdSetFillMode.h"
#include "Rasterizer.h"

bool CmdSetFillMode::Execute(const std::vector<std::string>& params)
{
    if (params.size() == 1)
    {
        if (params[0] == "wireframe")
        {
            Rasterizer::Get()->SetFillMode(FillMode::Wireframe);
            return true;
        }
        else if (params[0] == "solid")
        {
            Rasterizer::Get()->SetFillMode(FillMode::Solid);
            return true;
        }
        return false;
    }
    else return false;
}
