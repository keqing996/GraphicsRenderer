#include "MaterialUniformVariable.h"

namespace Renderer
{
    MaterialUniformVariable::MaterialUniformVariable(
        const std::string_view& uniformBlockName,
        const std::string_view& uniformValueName)
        : _uniformBlockName(uniformBlockName)
        , _uniformValueName(uniformValueName)
    {
    }

    auto MaterialUniformVariable::GetUniformBlockName() const -> const std::string_view&
    {
        return _uniformBlockName;
    }

    auto MaterialUniformVariable::GetUniformValueName() const -> const std::string_view&
    {
        return _uniformValueName;
    }
}
