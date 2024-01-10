#pragma once

#include "Define/Define.h"
#include "Renderer/Uniform/UniformElement.h"

namespace Renderer
{
    class UniformBlock;

    class UniformBuffer
    {
    public:
        explicit UniformBuffer(const Ptr<UniformBlock>& pBlock);
        virtual ~UniformBuffer() = default;

    public:
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        void UpdateElementData(Uniform::Element name, const std::byte* data);
        virtual void CommitElementData(Uniform::Element name) = 0;
        virtual void CommitBlockData() = 0;

    public:
        static Ptr<UniformBuffer> Create(const Ptr<UniformBlock>& pBlock);

    protected:
        Ptr<UniformBlock> _pUniformBlock;
        std::vector<std::byte> _rawData;
    };
}