#include "CmdPopMatrix.h"
#include "MatrixStack.h"
#include "VariableCache.h"

bool CmdPopMatrix::Execute(const std::vector<std::string>& params)
{
    MatrixStack::Get()->PopMatrix();

    return true;
}
