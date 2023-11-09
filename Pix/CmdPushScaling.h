#pragma once
#include "Command.h"

class CmdPushScaling : public Command
{
public:
	const char* GetName() override
	{
		return "PushScaling";
	}

	const char* GetDescription() override
	{
		return
			"PushScaling(x, y, z)\n"
			"\n"
			"- Sends a scaling matrix to the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

