#include "RendererPassForward.h"
#include "Scene/Scene.h"
#include "Scene/Component/CompCamera.h"
#include "Scene/Component/CompRenderer.h"
#include "Renderer/RenderCommand/RenderCommand.h"

namespace Renderer
{
    void RendererPassForward::Init()
    {
        _pUniBufferMvp = UniformBuffer::Create(
            UniformBlock::Create("MvpMatrices", {
                { "u_ModelMatrix", ShaderDataType::Matrix4x4 },
                { "u_ViewMatrix", ShaderDataType::Matrix4x4 },
                { "u_ProjectionMatrix", ShaderDataType::Matrix4x4 },
        }));
    }

    void RendererPassForward::Renderer(const Scene* pScene)
    {
        auto pMainCamera = pScene->GetMainCamera()->GetComponent<CompCamera>();

        // Prepare MVP uniform buffer
        const auto* viewMatData = reinterpret_cast<const std::byte*>((pMainCamera->GetViewMatrix()).data());
        const auto* projMatData = reinterpret_cast<const std::byte*>((pMainCamera->GetProjectionMatrix()).data());
        _pUniBufferMvp->Bind();
        _pUniBufferMvp->UpdateElementData("u_ViewMatrix", viewMatData);
        _pUniBufferMvp->UpdateElementData("u_ProjectionMatrix", projMatData);
        _pUniBufferMvp->CommitBlockData();
        _pUniBufferMvp->UnBind();

        for (const auto& pObj: pScene->GetAllObjects())
        {
            auto pRenderer = pObj->GetComponent<CompRenderer>();
            if (pRenderer == nullptr)
                continue;

            auto pAssemble = pRenderer->GetInputAssemble();
            auto pMat = pRenderer->GetMaterial();

            // Model Mat
            const auto* modelMatData = reinterpret_cast<const std::byte*>((pObj->GetModelMatrix()).data());
            _pUniBufferMvp->Bind();
            _pUniBufferMvp->UpdateElementData("u_ModelMatrix", modelMatData);
            _pUniBufferMvp->CommitElementData("u_ModelMatrix");
            _pUniBufferMvp->UnBind();

            // Draw Call
            RenderCommand::Submit<RendererPassType::Forward>(pAssemble, pMat);
        }
    }
}