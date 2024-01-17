#include "MaterialTexture.h"
#include "Renderer/Texture/TexturePool.h"

namespace Renderer
{
    MaterialTexture::MaterialTexture(const std::string& uniformName, int slot, const std::string& imagePath)
        : _uniformName(uniformName)
        , _imagePath(imagePath)
        , _slot(slot)
    {
        TexturePool::Preload(imagePath);
    }

    const std::string& MaterialTexture::GetUniformName() const
    {
        return _uniformName;
    }

    const std::string& MaterialTexture::GetImagePath() const
    {
        return _imagePath;
    }

    int MaterialTexture::GetSlot() const
    {
        return _slot;
    }
}
