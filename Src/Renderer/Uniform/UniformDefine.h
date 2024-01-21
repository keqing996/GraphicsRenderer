#pragma once

namespace Renderer::Uniform
{
    inline constexpr char MvpMatrices[] = "MvpMatrices";
    inline constexpr char MvpMatrices_ModelMatrix[] = "u_ModelMatrix";
    inline constexpr char MvpMatrices_ViewMatrix[] = "u_ViewMatrix";
    inline constexpr char MvpMatrices_ProjectionMatrix[] = "u_ProjectionMatrix";

    inline constexpr char MaterialProperty[] = "MaterialProperty";
    inline constexpr char MaterialProperty_CameraPosition[] = "u_CameraPosition";
    inline constexpr char MaterialProperty_SelfColor[] = "u_SelfColor";
    inline constexpr char MaterialProperty_SpecularShininess[] = "u_SpecularShininess";

}