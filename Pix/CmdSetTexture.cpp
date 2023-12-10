#include "CmdSetTexture.h"
#include "TextureCache.h"

bool CmdSetTexture::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	TextureCache::Get()->SetTexture(params[0]);
	return true;
}