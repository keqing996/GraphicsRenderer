#pragma once

#include "Renderer/RenderCommand/RenderCommandImpl.h"

namespace Renderer
{
    class RenderCommandOpenGL : public RenderCommandImpl
    {
    public:
        RenderCommandOpenGL();
        ~RenderCommandOpenGL() override = default;

    public:
        bool SetUp() override;
        void Destroy() override;
        void SwapBuffer() override;
        void ClearColor(const Eigen::Vector4f&) override;
        void Submit(const Ptr<InputAssemble>& pInputAssemble) override;

    public:
        const void* GetDeviceContextHandle() const;
        const void* GetRenderCoontextHandle() const;

    private:
        void* _hDeviceConext;
        void* _hRenderContext;

    };
}

