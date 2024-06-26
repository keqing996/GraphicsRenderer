#pragma once

#include "Pass/RendererPass.h"
#include "Renderer/Buffer/UniformBuffer.h"
#include "Renderer/Uniform/UniformBlock.h"
#include "RendererPipelineType.h"

class Scene;

namespace Renderer
{
    class RendererPipeline
    {
    public:
        RendererPipeline();

    public:
        void Renderer(const Scene* pScene);
        UniformBuffer* GetUniformBuffer(const std::string_view& name);

    public:
        static Ptr<RendererPipeline> CreateRendererPipeline(RendererPipelineType type);

    private:
        template<typename Pass>
        void AddPass()
        {
            Ptr<Pass> pPass = std::make_shared<Pass>();
            pPass->Init();
            Ptr<RendererPass> pTopPass = DynamicCast<RendererPass>(pPass);
            _passes.push_back(pTopPass);
        }

    private:
        std::vector<Ptr<RendererPass>> _passes;
        umap<std::string_view, Ptr<UniformBuffer>> _uniformMap;
    };

}