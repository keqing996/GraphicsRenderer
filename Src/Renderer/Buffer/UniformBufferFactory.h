#pragma once

#include <Helper/>
#include "Renderer/Uniform/UniformDefine.h"
#include "Renderer/Buffer/UniformBuffer.h"

namespace Renderer
{
    /*
    Ptr<UniformBuffer> CreateMvpMatrices()
    {
        return UniformBuffer::Create(
                        UniformBlock::Create(Uniform::Name::MvpMatrices, {
                            { Uniform::Element::MvpMatricesModelMatrix, ShaderDataType::Matrix4x4 },
                            { Uniform::Element::MvpMatricesViewMatrix, ShaderDataType::Matrix4x4 },
                            { Uniform::Element::MvpMatricesProjectionMatrix, ShaderDataType::Matrix4x4 },
                    }));
    }
    */
}

