#pragma once

#include <Helper/NonCopyable.h>

#include "Define/Define.h"
#include "Renderer/InputAssemble/InputAssemble.h"
#include "eigen/Eigen"

namespace Renderer
{
    class RenderCommandImpl : public Helper::NonCopyable
    {
    public:
        virtual ~RenderCommandImpl() = default;

    public:
        virtual bool SetUp() = 0;
        virtual void Destroy() = 0;
        virtual void SwapBuffer() = 0;
        virtual void ClearColor(const Eigen::Vector4f& color) = 0;
        virtual void Submit(const Ptr<InputAssemble>& pInputAssemble) = 0;
    };
}