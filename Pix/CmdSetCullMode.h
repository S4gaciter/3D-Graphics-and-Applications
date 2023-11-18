#pragma once
#include "Command.h"

class CmdSetCullMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetCullMode";
	}

	const char* GetDescription() override
	{
		return
			"SetCullMode(cullmode)\n"
			"\n"
			"- Sets the cull mode used for drawing triangles.\n"
			"- None, Back, Front";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

