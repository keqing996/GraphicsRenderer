#include <cassert>
#include <algorithm>
#include "UniformBuffer.h"
#include "Application/Application.h"
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

    void UniformBuffer::UpdateElementData(const std::string& name, const std::byte* data, int dataSize)
    {
        auto offset = _pUniformBlock->GetElementOffset(name);

        auto totalSize = _pUniformBlock->GetBlockSize();
        auto allowUpdateLength = totalSize - offset;
        assert(allowUpdateLength >= dataSize);

        ::memcpy(_rawData.data() + offset, data, dataSize);
    }

    void UniformBuffer::UpdateBlockData(const std::byte* data, int dataSize)
    {
        auto totalSize = _pUniformBlock->GetBlockSize();
        assert(totalSize >= dataSize);

        ::memcpy(_rawData.data(), data, dataSize);
        std::fill(_rawData.begin() + dataSize, _rawData.end(), std::byte { 0x00 });
    }
}
