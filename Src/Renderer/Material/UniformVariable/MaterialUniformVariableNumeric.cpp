#include "MaterialUniformVariableNumeric.h"

namespace Renderer
{
    template<>
    MaterialUniformVariableType MaterialUniformVariableNumeric<int>::GetType() const
    {
        return MaterialUniformVariableType::Float;
    }

    template<>
    const std::byte* MaterialUniformVariableNumeric<int>::GetData() const
    {
        return reinterpret_cast<const std::byte*>(&_value);
    }

    template<>
    MaterialUniformVariableType MaterialUniformVariableNumeric<unsigned int>::GetType() const
    {
        return MaterialUniformVariableType::Uint;
    }

    template<>
    const std::byte* MaterialUniformVariableNumeric<unsigned int>::GetData() const
    {
        return reinterpret_cast<const std::byte*>(&_value);
    }

    template<>
    MaterialUniformVariableType MaterialUniformVariableNumeric<float>::GetType() const
    {
        return MaterialUniformVariableType::Float;
    }

    template<>
    const std::byte* MaterialUniformVariableNumeric<float>::GetData() const
    {
        return reinterpret_cast<const std::byte*>(&_value);
    }

    template<>
    MaterialUniformVariableType MaterialUniformVariableNumeric<Eigen::Vector2f>::GetType() const
    {
        return MaterialUniformVariableType::Float2;
    }

    template<>
    const std::byte* MaterialUniformVariableNumeric<Eigen::Vector2f>::GetData() const
    {
        return reinterpret_cast<const std::byte*>(_value.data());
    }

    template<>
    MaterialUniformVariableType MaterialUniformVariableNumeric<Eigen::Vector3f>::GetType() const
    {
        return MaterialUniformVariableType::Float3;
    }

    template<>
    const std::byte* MaterialUniformVariableNumeric<Eigen::Vector3f>::GetData() const
    {
        return reinterpret_cast<const std::byte*>(_value.data());
    }

    template<>
    MaterialUniformVariableType MaterialUniformVariableNumeric<Eigen::Vector4f>::GetType() const
    {
        return MaterialUniformVariableType::Float4;
    }

    template<>
    const std::byte* MaterialUniformVariableNumeric<Eigen::Vector4f>::GetData() const
    {
        return reinterpret_cast<const std::byte*>(_value.data());
    }

}