#pragma once
#include "Command.h"
class CmdSetShading : public Command
{
public:
	const char* GetName() override
	{
		return "SetShading";
	}

	const char* GetDescription() override
	{
		return
			"SetShading(shademode)\n"
			"\n"
			"- Sets the shade mode.\n"
			"(Flat, Gouraud, Phong)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

