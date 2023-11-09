#pragma once
#include "Command.h"
class CmdPopMatrix : public Command
{
public:
	const char* GetName() override
	{
		return "PopMatrix";
	}

	const char* GetDescription() override
	{
		return
			"PopMatrix()\n"
			"\n"
			"- Removes the most recent matrix from the matrix stack.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

