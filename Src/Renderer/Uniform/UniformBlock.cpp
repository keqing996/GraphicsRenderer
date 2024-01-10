#include <Helper/Logger.h>
#include "UniformBlock.h"
#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Uniform/UniformBlockOpenGL.h"

namespace Renderer
{
    Ptr<UniformBlock> UniformBlock::Create(Uniform::Name name, const std::initializer_list<Element>& elements)
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

    UniformBlock::UniformBlock(Uniform::Name name)
        : _name(name)
    {
    }

    void UniformBlock::Init(const std::initializer_list<Element>& elements)
    {
        _uniformData = elements;

        UpdateOffset();
    }

    Uniform::Name UniformBlock::GetName() const
    {
        return _name;
    }

    int UniformBlock::GetElementOffset(Uniform::Element elementName) const
    {
        if (auto itr = _uniformOffsetMap.find(elementName); itr != _uniformOffsetMap.end())
            return itr->second;

        auto uniformNameStr = Uniform::NameHelper::NameToString(_name);
        auto uniformEleStr = Uniform::ElementHelper::ElementToString(elementName);
        Helper::Logger::LogError(std::format("Uniform block '{}' do not have '{}'", uniformNameStr, uniformEleStr));
        return -1;
    }

    int UniformBlock::GetElementSize(Uniform::Element elementName) const
    {
        if (auto itr = _uniformSizeMap.find(elementName); itr != _uniformSizeMap.end())
            return itr->second;

        auto uniformNameStr = Uniform::NameHelper::NameToString(_name);
        auto uniformEleStr = Uniform::ElementHelper::ElementToString(elementName);
        Helper::Logger::LogError(std::format("Uniform block '{}' do not have '{}'", uniformNameStr, uniformEleStr));
        return -1;
    }

    int UniformBlock::GetBlockSize() const
    {
        return _totalSize;
    }
}
