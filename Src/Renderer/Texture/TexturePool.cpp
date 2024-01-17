#include "TexturePool.h"
#include "Renderer/Assets/AssetsPool.hpp"

namespace Renderer
{
    Ptr<Texture2d> TexturePool::GetTexture(const std::string& imagePath)
    {
        auto itr = _texture2dPool.find(imagePath);
        if (itr != _texture2dPool.end())
            return itr->second;

        Preload(imagePath);

        return _texture2dPool[imagePath];
    }

    void TexturePool::Preload(const std::string& imagePath)
    {
        if (_texture2dPool.contains(imagePath))
            return;

        auto pImage = AssetsPool<Image>::Get(imagePath);
        Ptr<Texture2d> pTexture = Texture2d::Create();
        pTexture->PushData(pImage);

        _texture2dPool[imagePath] = pTexture;
    }
}
