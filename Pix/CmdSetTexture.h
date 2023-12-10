#pragma once

#include "Command.h"

class CmdSetTexture : Command
{
public:
	const char* GetName() override
	{
		return "SetTexture";
	}
	const char* GetDescription() override
	{
		return "SetTexture(fileName)\n"
			"\n"
			"Stores a texture and sets as current.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

