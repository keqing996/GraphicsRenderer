#pragma once

#include <string>

namespace Renderer
{
    class MaterialTexture
    {
    public:
        MaterialTexture(const std::string& uniformName, int slot, const std::string& imagePath);

    public:
        const std::string& GetUniformName() const;
        const std::string& GetImagePath() const;
        int GetSlot() const;

    private:
        std::string _uniformName;
        std::string _imagePath;
        int _slot;
    };
}