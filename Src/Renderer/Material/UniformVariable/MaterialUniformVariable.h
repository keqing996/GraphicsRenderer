#pragma once

#include "Define/Define.h"
#include "MaterialUniformVariableType.h"
#include "Renderer/Shader/ShaderProgram.h"

namespace Renderer
{
    class MaterialUniformVariable
    {
    public:
        MaterialUniformVariable(const std::string_view& uniformBlockName, const std::string_view& uniformValueName);

    public:
        virtual auto GetType() const -> MaterialUniformVariableType = 0;
        virtual auto GetData() const -> const std::byte* = 0;

        auto GetUniformBlockName() const -> const std::string_view&;
        auto GetUniformValueName() const -> const std::string_view&;

    protected:
        std::string_view _uniformBlockName;
        std::string_view _uniformValueName;
    };

}