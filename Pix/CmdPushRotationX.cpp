#include "CmdPushRotationX.h"
#include "MatrixStack.h"
#include "VariableCache.h"

bool CmdPushRotationX::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }

    VariableCache* vc = VariableCache::Get();
    float deg = vc->GetFloat(params[0]);

    MatrixStack::Get()->PushRotationX(deg * 3.1416f / 180.0f);

    return true;
}
