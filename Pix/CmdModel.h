#pragma once

#include "Command.h"
#include "ModelCache.h"
#include "PrimitivesManager.h"

class CmdModel : public Command
{
public:
	const char* GetName() override
	{
		return "Model";
	}
	const char* GetDescription() override
	{
		return "Model(filename)\n"
			"\n"
			"- stores a set of model vertices.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

