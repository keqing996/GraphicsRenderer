#pragma once

#include "Define/Define.h"

class Scene;

namespace Renderer
{
    class UniformBlock;
    class UniformBuffer;
    class RendererPipeline;

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
        virtual void Renderer(RendererPipeline* pPipeLine, const Scene* pScene) = 0;
    };
}