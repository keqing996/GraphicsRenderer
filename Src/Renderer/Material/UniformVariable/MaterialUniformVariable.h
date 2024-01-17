#pragma once

#include "Define/Define.h"
#include "MaterialUniformVariableType.h"
#include "Renderer/Shader/ShaderProgram.h"

namespace Renderer
{
    class MaterialUniformVariable
    {
    public:
        MaterialUniformVariable(const std::string& uniformBlockName, const std::string& uniformValueName);

    public:
        virtual auto GetType() const -> MaterialUniformVariableType = 0;
        virtual auto GetData() const -> const std::byte* = 0;

        auto GetUniformBlockName() const -> const std::string&;
        auto GetUniformValueName() const -> const std::string&;

    protected:
        std::string _uniformBlockName;
        std::string _uniformValueName;
    };

}