#pragma once

#include "Command.h"

class CmdSetClipping : public Command
{
public:
	const char* GetName() override
	{
		return "SetClipping";
	}

	const char* GetDescription() override
	{
		return
			"SetClipping(bool)\n"
			"\n"
			"- Sets whether or not geometry is clipped and culled.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};