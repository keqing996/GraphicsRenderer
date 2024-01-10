#pragma once

#include <string>
#include <Helper/NonConstructible.h>

namespace Renderer
{
    class UniformDefine: Helper::NonConstructible
    {
    public:
        inline static std::string MvpMatrices = "MvpMatrices";
        inline static std::string MvpMatrices_ModelMatrix = "u_ModelMatrix";
        inline static std::string MvpMatrices_ViewMatrix = "u_ViewMatrix";
        inline static std::string MvpMatrices_ProjectionMatrix = "u_ProjectionMatrix";

    };
}