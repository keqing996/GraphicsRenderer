#pragma once

#include <eigen/Eigen>
#include <unordered_map>
#include "Define/Define.h"
#include "Scene/Component/Component.h"
#include "Scene/Component/ComponentType.h"

class SceneObject
{
public:
    Eigen::Vector3f& GetPosition();
    Eigen::Quaternionf& GetRotation();
    Eigen::Vector3f& GetScale();

    template<class T, class... Types>
    void AddComponent(Types&&... Args)
    {
        ComponentType t = T::GetType();
        _componentMap[t] = DynamicCast<Component>(std::make_shared<T>(std::forward<Types&&>(Args)...));
        _componentMap[t]->SetSceneObject(this);
    }

    template<class T>
    Ptr<T> GetComponent()
    {
        ComponentType t = T::GetType();
        return DynamicCast<T>(_componentMap[t]);
    }

private:
    Eigen::Vector3f _position = Eigen::Vector3f::Zero();
    Eigen::Quaternionf _rotation = Eigen::Quaternionf::Identity();
    Eigen::Vector3f _scale = Eigen::Vector3f::Ones();

    umap<ComponentType, Ptr<Component>> _componentMap;
};