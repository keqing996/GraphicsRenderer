#include "RendererPassForward.h"
#include "Scene/Scene.h"
#include "Scene/Component/CompCamera.h"
#include "Scene/Component/CompRenderer.h"
#include "Renderer/RenderCommand/RenderCommand.h"
#include "Renderer/Buffer/UniformDefine.h"

namespace Renderer
{
    void RendererPassForward::Init()
    {
    }

    void RendererPassForward::Renderer(const Scene* pScene)
    {
        auto pMainCamera = pScene->GetMainCamera()->GetComponent<CompCamera>();

        // Prepare MVP uniform buffer
        const auto* viewMatData = reinterpret_cast<const std::byte*>((pMainCamera->GetViewMatrix()).data());
        const auto* projMatData = reinterpret_cast<const std::byte*>((pMainCamera->GetProjectionMatrix()).data());

        auto pUniBufferMvp = pScene->GetRendererPipeline()->GetUniformBuffer(UniformDefine::MvpMatrices);
        pUniBufferMvp->Bind();
        pUniBufferMvp->UpdateElementData(UniformDefine::MvpMatrices_ViewMatrix, viewMatData);
        pUniBufferMvp->UpdateElementData(UniformDefine::MvpMatrices_ProjectionMatrix, projMatData);
        pUniBufferMvp->CommitBlockData();
        pUniBufferMvp->UnBind();

        for (const auto& pObj: pScene->GetAllObjects())
        {
            auto pRenderer = pObj->GetComponent<CompRenderer>();
            if (pRenderer == nullptr)
                continue;

            auto pAssemble = pRenderer->GetInputAssemble();
            auto pMat = pRenderer->GetMaterial();

            // Model Mat
            const auto* modelMatData = reinterpret_cast<const std::byte*>((pObj->GetModelMatrix()).data());
            pUniBufferMvp->Bind();
            pUniBufferMvp->UpdateElementData(UniformDefine::MvpMatrices_ModelMatrix, modelMatData);
            pUniBufferMvp->CommitElementData(UniformDefine::MvpMatrices_ModelMatrix);
            pUniBufferMvp->UnBind();

            // Draw Call
            RenderCommand::Submit<RendererPassType::Forward>(pAssemble, pMat);
        }
    }
}