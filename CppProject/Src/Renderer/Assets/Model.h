#pragma once

#include <unordered_map>
#include "Define/Define.h"
#include "AssetsPool.hpp"
#include "Mesh.h"

namespace Renderer
{
    class Model
    {
    public:
        friend class AssetsPool<Model>;

    private:
        void Load(const std::string& path);

    private:
        std::unordered_map<std::string, Ptr<Mesh>> _meshMap;
    };
}