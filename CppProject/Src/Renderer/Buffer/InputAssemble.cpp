#include "InputAssemble.h"

#include "Application/Application.h"
#include "RendererHardwareInterface/OpenGL/Buffer/InputAssembleOpenGL.h"

namespace Renderer
{

    Ptr<InputAssemble> InputAssemble::Create()
    {
        switch (Application::GetRenderApi())
        {
            case RendererApi::OpenGL:
                return std::make_shared<InputAssembleOpenGL>();
            case RendererApi::Vulkan:
                break;
            case RendererApi::D3D11:
                break;
            case RendererApi::D3D12:
                break;
        }

        return nullptr;
    }

    void InputAssemble::SetInputLayout(const InputLayout& layout)
    {
        _inputLayout = layout;
    }

    void InputAssemble::SetVertexBuffer(Ptr<VertexBuffer>& pVertexBuffer)
    {
        _pVertexBuffer = pVertexBuffer;
    }

    void InputAssemble::SetIndexBuffer(Ptr<IndexBuffer>& pIndexBuffer)
    {
        _pIndexBuffer = pIndexBuffer;
    }

    const InputLayout& InputAssemble::GetInputLayout() const
    {
        return _inputLayout;
    }

    const Ptr<VertexBuffer>& InputAssemble::GetVertexBuffer() const
    {
        return _pVertexBuffer;
    }

    const Ptr<IndexBuffer>& InputAssemble::GetIndexBuffer() const
    {
        return _pIndexBuffer;
    }
}