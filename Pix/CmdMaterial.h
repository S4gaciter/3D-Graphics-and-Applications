#pragma once
#include "Command.h"

class CmdSetMaterialAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialAmbient";
	}
	const char* GetDescription() override
	{
		return "Sets the material ambient (r, g, b)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetMaterialDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialDiffuse";
	}
	const char* GetDescription() override
	{
		return "Sets the material diffuse (r, g, b)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetMaterialSpecular : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialSpecular";
	}
	const char* GetDescription() override
	{
		return "Sets the material specular (r, g, b)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdSetMaterialShininess : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialShininess";
	}
	const char* GetDescription() override
	{
		return "Sets the material shininess (float)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};