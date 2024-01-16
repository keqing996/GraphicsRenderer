#pragma once

#include "Define/Define.h"
#include "Renderer/Shader/ShaderProgram.h"
#include "UniformVariable/MaterialUniformVariable.h"
#include "Renderer/Pipeline/Pass/RendererPassType.h"

namespace Renderer
{
    class Material
    {
    public:
        explicit Material(const std::string& materialPath);

    public:
        Ptr<ShaderProgram> GetShader(RendererPassType pass) const;
        const std::vector<Ptr<MaterialUniformVariable>>* GetUniformVariables(RendererPassType pass) const;

    private:
        umap<RendererPassType, Ptr<ShaderProgram>> _passShaderMap;
        umap<RendererPassType, std::vector<Ptr<MaterialUniformVariable>>> _passUniVars;
    };
}