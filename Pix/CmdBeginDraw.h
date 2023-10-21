#pragma once

#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "BeginDraw";
	}

	const char* GetDescription() override
	{
		return
			"BeginDraw(topology)\n"
			"\n"
			"- Begins adding vertices to draw with EndDraw to the vertex buffer.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};