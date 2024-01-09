#pragma once

#include "Define/Define.h"
#include "UniformBlock.h"

namespace Renderer
{
    class UniformBuffer
    {
    public:
        explicit UniformBuffer(const Ptr<UniformBlock>& pBlock);
        virtual ~UniformBuffer() = default;

    public:
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        void UpdateElementData(const std::string& name, const std::byte* data, int dataSize);
        void UpdateBlockData(const std::byte* data, int dataSize);
        virtual void CommitElementData(const std::string& name) = 0;
        virtual void CommitBlockData() = 0;

    public:
        static Ptr<UniformBuffer> Create(const Ptr<UniformBlock>& pBlock);

    protected:
        Ptr<UniformBlock> _pUniformBlock;
        std::vector<std::byte> _rawData;
    };
}