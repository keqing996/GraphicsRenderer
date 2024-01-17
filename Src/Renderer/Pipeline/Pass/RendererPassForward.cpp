#include <Helper/Logger.h>
#include "RendererPassForward.h"
#include "Scene/Scene.h"
#include "Scene/Component/CompCamera.h"
#include "Scene/Component/CompRenderer.h"
#include "Renderer/RenderCommand/RenderCommand.h"
#include "Renderer/Uniform/UniformDefine.h"
#include "Renderer/Pipeline/RendererPipeline.h"

namespace Renderer
{
    void RendererPassForward::Init()
    {
    }

    void RendererPassForward::Renderer(RendererPipeline* pPipeLine, const Scene* pScene)
    {
        auto pMainCamera = pScene->GetMainCamera()->GetComponent<CompCamera>();

        // Prepare MVP uniform buffer
        const auto* viewMatData = reinterpret_cast<const std::byte*>((pMainCamera->GetViewMatrix()).data());
        const auto* projMatData = reinterpret_cast<const std::byte*>((pMainCamera->GetProjectionMatrix()).data());

        auto pUniBufferMvp = pPipeLine->GetUniformBuffer(Uniform::MvpMatrices);
        pUniBufferMvp->Bind();
        pUniBufferMvp->UpdateElementData(Uniform::MvpMatrices_ViewMatrix, viewMatData);
        pUniBufferMvp->UpdateElementData(Uniform::MvpMatrices_ProjectionMatrix, projMatData);
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
            pUniBufferMvp->UpdateElementData(Uniform::MvpMatrices_ModelMatrix, modelMatData);
            pUniBufferMvp->CommitElementData(Uniform::MvpMatrices_ModelMatrix);
            pUniBufferMvp->UnBind();

            // Material Shader
            auto pShader = pMat->GetShader(RendererPassType::Forward);
            pShader->Bind();

            // Material Uniform
            auto pUniformVarVec = pMat->GetUniformVariables(RendererPassType::Forward);
            if (pUniformVarVec != nullptr)
            {
                for (auto pUniVar : *pUniformVarVec)
                {
                    auto uniBlockName = pUniVar->GetUniformBlockName();
                    const auto pUniBlockBuffer = pPipeLine->GetUniformBuffer(uniBlockName);
                    if (pUniBlockBuffer == nullptr)
                    {
                        Helper::Logger::LogWarn("Pipeline get uniform buffer {} failed.", uniBlockName);
                        continue;
                    }

                    auto uniVarName = pUniVar->GetUniformValueName();
                    pUniBlockBuffer->Bind();
                    pUniBlockBuffer->UpdateElementData(uniVarName, pUniVar->GetData());
                    pUniBlockBuffer->CommitElementData(uniVarName);
                    pUniBlockBuffer->UnBind();
                }
            }

            // Texture
            auto pUniformTexVec = pMat->GetTextures(RendererPassType::Forward);
            if (pUniformTexVec != nullptr)
            {
                for (auto pUniTex : *pUniformTexVec)
                {
                    auto pTex = pUniTex->GetTexture();
                    auto slot = pUniTex->GetSlot();
                    pTex->Bind(slot);
                    pShader->SetUniformInt(pUniTex->GetUniformName(), slot);
                }
            }

            // Draw Call
            RenderCommand::Submit(pAssemble);
        }
    }
}