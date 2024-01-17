#include "MaterialTexture.h"
#include "Renderer/Assets/AssetsPool.hpp"

namespace Renderer
{
    MaterialTexture::MaterialTexture(const std::string& uniformName, int slot, const std::string& imagePath)
        : _uniformName(uniformName)
        , _slot(slot)
    {
        auto pImage = AssetsPool<Image>::Get(imagePath);
        _pTexture = Texture2d::Create();
        _pTexture->PushData(pImage);
    }

    const std::string& MaterialTexture::GetUniformName() const
    {
        return _uniformName;
    }

    int MaterialTexture::GetSlot() const
    {
        return _slot;
    }

    const Ptr<Texture2d>& MaterialTexture::GetTexture() const
    {
        return _pTexture;
    }
}
