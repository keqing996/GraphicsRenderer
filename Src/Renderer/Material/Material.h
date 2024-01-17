#pragma once

#include "Define/Define.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "UniformVariable/MaterialUniformVariable.h"
#include "UniformVariable/MaterialTexture.h"
#include "Renderer/Pipeline/Pass/RendererPassType.h"

namespace Renderer
{
    class Material
    {
    public:
        explicit Material(const std::string& materialPath);

    public:
        auto GetShader(RendererPassType pass) const -> Ptr<ShaderProgram>;
        auto GetUniformVariables(RendererPassType pass) const -> const std::vector<Ptr<MaterialUniformVariable>>*;
        auto GetTextures(RendererPassType pass) const -> const std::vector<Ptr<MaterialTexture>>*;

    private:
        umap<RendererPassType, Ptr<ShaderProgram>> _passShaderMap;
        umap<RendererPassType, std::vector<Ptr<MaterialUniformVariable>>> _passUniVars;
        umap<RendererPassType, std::vector<Ptr<MaterialTexture>>> _passTextures;
    };
}