#pragma once
#include "Command.h"

class CmdPushRotationY : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationY";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationY(deg)\n"
			"\n"
			"- Sends a rotation matrix to the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

