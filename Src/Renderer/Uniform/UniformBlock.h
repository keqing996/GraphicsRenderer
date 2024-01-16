#pragma once

#include <string>
#include <vector>
#include "Define/Define.h"
#include "Renderer/Shader/ShaderDataType.h"

namespace Renderer
{
    class UniformBlock
    {
    public:
        struct Element
        {
            std::string_view name;
            ShaderDataType shaderDataType;
        };

    public:
        virtual ~UniformBlock() = default;

    public:
        static Ptr<UniformBlock> Create(const std::string_view& name, const std::initializer_list<Element>& elements);

    public:
        const std::string_view& GetName() const;
        int GetElementOffset(const std::string_view& elementName) const;
        int GetElementSize(const std::string_view& elementName) const;
        int GetBlockSize() const;

    protected:
        explicit UniformBlock(const std::string_view& name);
        void Init(const std::initializer_list<Element>& elements);
        virtual void UpdateOffset() = 0;

    protected:
        std::string_view _name;
        std::vector<Element> _uniformData;
        umap<std::string_view, int> _uniformOffsetMap;
        umap<std::string_view, int> _uniformSizeMap;
        int _totalSize = 0;
    };
}