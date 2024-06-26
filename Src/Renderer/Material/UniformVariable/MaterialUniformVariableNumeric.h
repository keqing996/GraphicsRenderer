#pragma once

#include "MaterialUniformVariable.h"

namespace Renderer
{
    template<typename T>
    class MaterialUniformVariableNumeric: public MaterialUniformVariable
    {
    public:
        MaterialUniformVariableNumeric(const std::string& uniformBlockName, const std::string& uniformValueName, const T& value)
            : MaterialUniformVariable(uniformBlockName, uniformValueName)
            , _value(value)
        {
        }

    public:
        // imp in cpp file
        auto GetType() const -> MaterialUniformVariableType override;
        auto GetData() const -> const std::byte* override;

    private:
        T _value;
    };
}