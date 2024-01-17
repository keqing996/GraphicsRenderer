#pragma once

#include <string>
#include "Renderer/Texture/Texture2d.h"

namespace Renderer
{
    class MaterialTexture
    {
    public:
        MaterialTexture(const std::string& uniformName, int slot, const std::string& imagePath);

    public:
        const std::string& GetUniformName() const;
        int GetSlot() const;
        const Ptr<Texture2d>& GetTexture() const;

    private:
        std::string _uniformName;
        int _slot;
        Ptr<Texture2d> _pTexture;
    };
}