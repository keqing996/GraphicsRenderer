#pragma once

#include "Define/Define.h"
#include "SceneObject.h"
#include "Component/CompCamera.h"

class Scene
{
public:
    auto AddObject(const Ptr<SceneObject>& pObj) -> void;

    auto SetMainCamera(Ptr<SceneObject>& pObj) -> void;
    auto GetMainCamera() const -> const Ptr<SceneObject>&;

    auto GetAllObjects() const -> const std::vector<Ptr<SceneObject>>&;
    auto FindFirstObjectByName(const std::string& name) const -> SceneObject*;

private:
    std::vector<Ptr<SceneObject>> _sceneObjects;
    Ptr<SceneObject> _pMainCamera = nullptr;
};