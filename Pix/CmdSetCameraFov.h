#pragma once
#include "Command.h"
class CmdSetCameraFov : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFov";
	}

	const char* GetDescription() override
	{
		return
			"SetCameraFov(deg)\n"
			"\n"
			"- Sets the near plane of the camera.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

