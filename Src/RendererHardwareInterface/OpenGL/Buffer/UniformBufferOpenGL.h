#pragma once

#include "Renderer/Buffer/UniformBuffer.h"

namespace Renderer
{
    class UniformBufferOpenGL: public UniformBuffer
    {
    public:
        explicit UniformBufferOpenGL(const Ptr<UniformBlock>& pBlock);
        ~UniformBufferOpenGL() override;

    public:
        void Bind() const override;
        void UnBind() const override;
        void CommitElementData(const std::string_view& name) override;
        void CommitBlockData() override;

    private:
        unsigned int _bufferId = 0;
        unsigned int _bindingPoint = 0;
    };
}