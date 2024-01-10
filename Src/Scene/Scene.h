#pragma once

#include "Define/Define.h"
#include "Renderer/Pipeline/RendererPipelineType.h"
#include "Renderer/Pipeline/RendererPipeline.h"
#include "SceneObject.h"
#include "Component/CompCamera.h"

class Scene
{
public:
    auto SetRendererPipeline(Renderer::RendererPipelineType type) -> void;
    auto GetRendererPipeline() const -> Renderer::RendererPipeline*;

    auto AddObject(const Ptr<SceneObject>& pObj) -> void;
    auto Render() -> void;

    auto SetMainCamera(Ptr<SceneObject>& pObj) -> void;
    auto GetMainCamera() const -> const Ptr<SceneObject>&;

    auto GetAllObjects() const -> const std::vector<Ptr<SceneObject>>&;
    auto FindFirstObjectByName(const std::string& name) const -> SceneObject*;

private:
    std::vector<Ptr<SceneObject>> _sceneObjects;
    Ptr<SceneObject> _pMainCamera = nullptr;

    Ptr<Renderer::RendererPipeline> _pRendererPipeline = nullptr;
};