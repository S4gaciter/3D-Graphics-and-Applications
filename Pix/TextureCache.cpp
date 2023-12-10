#include "TextureCache.h"


TextureCache* TextureCache::Get()
{
	static TextureCache sInstance;
	return &sInstance;
}

void TextureCache::Clear()
{
	mTextures.clear();
	mCurrentTexture = nullptr;
}

void TextureCache::SetTexture(const std::string& fileName)
{
	auto iter = std::find_if(mTextures.begin(), mTextures.end(), 
		[fileName](auto& texture) {return texture->GetFileName() == fileName; });
	if (iter != mTextures.end())
	{
		mCurrentTexture = iter->get();
	}
	else
	{
		auto& texture = mTextures.emplace_back(std::make_unique<Texture>());
		texture->Load(fileName);
		mCurrentTexture = texture.get();
	}
}

X::Color TextureCache::SampleColor(const X::Color& uv) const
{
	X::Color color = uv;
	if (mCurrentTexture != nullptr && uv.z < 0.0f)
	{
		float u = uv.x / uv.w;
		float v = uv.y / uv.w;
		color = mCurrentTexture->GetPixel(u, v);
	}
	return color;
}