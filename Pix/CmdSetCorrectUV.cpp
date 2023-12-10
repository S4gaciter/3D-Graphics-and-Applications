#include "CmdSetCorrectUV.h"
#include "PrimitivesManager.h"

bool CmdSetCorrectUV::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	bool correct = params[0] == "true";
	PrimitivesManager::Get()->SetCorrectUV(correct);
	return true;
}