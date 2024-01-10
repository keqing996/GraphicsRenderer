#pragma once

#include <string>
#include <vector>
#include "UniformName.h"
#include "UniformElement.h"
#include "Define/Define.h"
#include "Renderer/Shader/ShaderDataType.h"

namespace Renderer
{
    class UniformBlock
    {
    public:
        struct Element
        {
            Uniform::Element name;
            ShaderDataType shaderDataType;
        };

    public:
        virtual ~UniformBlock() = default;

    public:
        static Ptr<UniformBlock> Create(Uniform::Name name, const std::initializer_list<Element>& elements);

    public:
        Uniform::Name GetName() const;
        int GetElementOffset(Uniform::Element elementName) const;
        int GetElementSize(Uniform::Element elementName) const;
        int GetBlockSize() const;

    protected:
        explicit UniformBlock(Uniform::Name name);
        void Init(const std::initializer_list<Element>& elements);
        virtual void UpdateOffset() = 0;

    protected:
        Uniform::Name _name;
        std::vector<Element> _uniformData;
        umap<Uniform::Element, int> _uniformOffsetMap;
        umap<Uniform::Element, int> _uniformSizeMap;
        int _totalSize = 0;
    };
}