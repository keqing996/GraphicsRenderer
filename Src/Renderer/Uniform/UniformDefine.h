#pragma once

#include <string>

namespace Renderer::Uniform
{
    inline std::string MvpMatrices = "MvpMatrices";
    inline std::string MvpMatrices_ModelMatrix = "u_ModelMatrix";
    inline std::string MvpMatrices_ViewMatrix = "u_ViewMatrix";
    inline std::string MvpMatrices_ProjectionMatrix = "u_ProjectionMatrix";

}