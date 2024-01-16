#pragma once

#include <Helper/NonConstructible.h>
#include "Renderer/Buffer/UniformBuffer.h"
#include "Renderer/Uniform/UniformDefine.h"
#include "Renderer/Uniform/UniformBlock.h"

namespace Renderer
{
    class UniformBufferFactory: public Helper::NonConstructible
    {
    public:
        template<const char* name>
        static Ptr<UniformBuffer> Create()
        {
            if constexpr (name == Uniform::MvpMatrices)
            {
                return UniformBuffer::Create(
                    UniformBlock::Create(Uniform::MvpMatrices,{
                        { Uniform::MvpMatrices_ModelMatrix, ShaderDataType::Matrix4x4 },
                        { Uniform::MvpMatrices_ViewMatrix, ShaderDataType::Matrix4x4 },
                        { Uniform::MvpMatrices_ProjectionMatrix, ShaderDataType::Matrix4x4 }
                    }));
            }

            return nullptr;
        }
    };
}

