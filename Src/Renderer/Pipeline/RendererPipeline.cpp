#include "RendererPipeline.h"
#include "Pass/RendererPassForward.h"
#include "Renderer/Buffer/UniformBufferFactory.h"

namespace Renderer
{
    RendererPipeline::RendererPipeline()
    {
        _uniformMap[Uniform::Name::MvpMatrices] = Uniform::CreateMvpMatrices<Uniform::Name::MvpMatrices>();
    }

    void RendererPipeline::Renderer(const Scene* pScene)
    {
        for (const auto& pPass : _passes)
            pPass->Renderer(pScene);
    }

    UniformBuffer* RendererPipeline::GetUniformBuffer(Uniform::Name name)
    {
        const auto itr = _uniformMap.find(name);
        if (itr == _uniformMap.end())
            return nullptr;

        return (itr->second).get();
    }

    Ptr<RendererPipeline> RendererPipeline::CreateRendererPipeline(RendererPipelineType type)
    {
        Ptr<RendererPipeline> pPipe = std::make_shared<RendererPipeline>();

        switch (type)
        {
            case RendererPipelineType::Forward:
            {
                pPipe->AddPass<RendererPassForward>();
                break;
            }
            case RendererPipelineType::Deferred:
            case RendererPipelineType::ForwardPlus:
                break;
        }

        return pPipe;
    }
}