#include <Helper/Logger.h>
#include "UniformBlock.h"
#include "UniformDefine.h"
#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Uniform/UniformBlockOpenGL.h"

namespace Renderer
{
    Ptr<UniformBlock> UniformBlock::Create(const std::string_view& name, const std::initializer_list<Element>& elements)
    {
        Ptr<UniformBlock> pResult = nullptr;

        switch (Application::GetRenderApi())
        {
            case RendererApi::OpenGL:
                pResult = std::make_shared<UniformBlockOpenGL>(name);
                break;
            case RendererApi::Vulkan:
                break;
            case RendererApi::D3D11:
                break;
            case RendererApi::D3D12:
                break;
        }

        if (pResult != nullptr)
            pResult->Init(elements);

        return pResult;
    }

    UniformBlock::UniformBlock(const std::string_view& name)
        : _name(name)
    {
    }

    void UniformBlock::Init(const std::initializer_list<Element>& elements)
    {
        _uniformData = elements;

        UpdateOffset();
    }

    const std::string_view& UniformBlock::GetName() const
    {
        return _name;
    }

    int UniformBlock::GetElementOffset(const std::string_view& elementName) const
    {
        if (auto itr = _uniformOffsetMap.find(elementName); itr != _uniformOffsetMap.end())
            return itr->second;

        Helper::Logger::LogError(std::format("Uniform block '{}' do not have '{}'", _name, elementName));
        return -1;
    }

    int UniformBlock::GetElementSize(const std::string_view& elementName) const
    {
        if (auto itr = _uniformSizeMap.find(elementName); itr != _uniformSizeMap.end())
            return itr->second;

        Helper::Logger::LogError(std::format("Uniform block '{}' do not have '{}'", _name, elementName));
        return -1;
    }

    int UniformBlock::GetBlockSize() const
    {
        return _totalSize;
    }
}
