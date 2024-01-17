#pragma once

#include <Helper/NonConstructible.h>
#include <ThirdParty/XXHash/XXHashMap.h>
#include "Texture2d.h"

namespace Renderer
{
    class TexturePool: public Helper::NonConstructible
    {
    public:
        static Ptr<Texture2d> GetTexture(const std::string& imagePath);
        static void Preload(const std::string& imagePath);

    private:
        inline static XXHashMap<std::string, Ptr<Texture2d>> _texture2dPool;
    };
}