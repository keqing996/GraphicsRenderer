#pragma once

#include "Define/Define.h"

class Scene;

namespace Renderer
{
    class UniformBlock;
    class UniformBuffer;

    class RendererPass
    {
    public:
        struct PassUniform
        {
            Ptr<UniformBlock> pUniformBlock;
            Ptr<UniformBuffer> pUniformBuffer;
        };

    public:
        virtual void Init() = 0;
        virtual void Renderer(const Scene* pScene) = 0;
    };
}