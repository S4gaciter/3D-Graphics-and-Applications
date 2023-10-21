#include "CmdEndDraw.h"
#include "PrimitivesManager.h"

bool CmdEndDraw::Execute(const std::vector<std::string>& params)
{
    return PrimitivesManager::Get()->EndDraw();
}
