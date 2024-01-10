#pragma once

#include "Renderer/Uniform/UniformName.h"
#include "Renderer/Buffer/UniformBuffer.h"

namespace Renderer::Uniform
{
    template<Uniform::Name uniformName>
    Ptr<UniformBuffer> CreateMvpMatrices()
    {
        if constexpr (uniformName == Uniform::Name::MvpMatrices)
        {
            return UniformBuffer::Create(
                        UniformBlock::Create(Uniform::Name::MvpMatrices, {
                            { Uniform::Element::MvpMatricesModelMatrix, ShaderDataType::Matrix4x4 },
                            { Uniform::Element::MvpMatricesViewMatrix, ShaderDataType::Matrix4x4 },
                            { Uniform::Element::MvpMatricesProjectionMatrix, ShaderDataType::Matrix4x4 },
                    }));
        }

        return nullptr;
    }
}

