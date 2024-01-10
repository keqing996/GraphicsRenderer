#include "UniformBufferFactory.h"
#include "UniformDefine.h"

namespace Renderer
{
    Ptr<UniformBuffer> UniformFactory::CreateMvpMatrices()
    {
        return UniformBuffer::Create(
            UniformBlock::Create(UniformDefine::MvpMatrices, {
                { UniformDefine::MvpMatrices_ModelMatrix, ShaderDataType::Matrix4x4 },
                { UniformDefine::MvpMatrices_ViewMatrix, ShaderDataType::Matrix4x4 },
                { UniformDefine::MvpMatrices_ProjectionMatrix, ShaderDataType::Matrix4x4 },
        }));
    }
}
