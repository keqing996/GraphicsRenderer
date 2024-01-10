#include <cassert>
#include <algorithm>
#include "UniformBuffer.h"
#include "Application/Application.h"
#include "Renderer/Uniform/UniformBlock.h"
#include "RendererHardwareInterface/OpenGL/Buffer/UniformBufferOpenGL.h"

namespace Renderer
{
    Ptr<UniformBuffer> UniformBuffer::Create(const Ptr<UniformBlock>& pBlock)
    {
        switch (Application::GetRenderApi())
        {
            case RendererApi::OpenGL:
                return std::make_shared<UniformBufferOpenGL>(pBlock);
            case RendererApi::Vulkan:
                break;
            case RendererApi::D3D11:
                break;
            case RendererApi::D3D12:
                break;
        }

        return nullptr;
    }

    UniformBuffer::UniformBuffer(const Ptr<UniformBlock>& pBlock)
        : _pUniformBlock(pBlock)
    {
        // raw data
        _rawData.resize(pBlock->GetBlockSize());
        std::ranges::fill(_rawData, std::byte { 0x00 });
    }

    void UniformBuffer::UpdateElementData(Uniform::Element name, const std::byte* data)
    {
        auto offset = _pUniformBlock->GetElementOffset(name);
        auto dataSize = _pUniformBlock->GetElementSize(name);

        auto totalSize = _pUniformBlock->GetBlockSize();
        auto allowUpdateLength = totalSize - offset;
        assert(allowUpdateLength >= dataSize);

        ::memcpy(_rawData.data() + offset, data, dataSize);
    }
}
