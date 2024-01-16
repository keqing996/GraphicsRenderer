#pragma once

#include <string>
#include <vector>
#include <ThirdParty/XXHash/XXHashMap.h>
#include "Define/Define.h"
#include "Renderer/Shader/ShaderDataType.h"

namespace Renderer
{
    class UniformBlock
    {
    public:
        struct Element
        {
            std::string name;
            ShaderDataType shaderDataType;
        };

    public:
        virtual ~UniformBlock() = default;

    public:
        static Ptr<UniformBlock> Create(const std::string& name, const std::initializer_list<Element>& elements);

    public:
        const std::string& GetName() const;
        int GetElementOffset(const std::string& elementName) const;
        int GetElementSize(const std::string& elementName) const;
        int GetBlockSize() const;

    protected:
        explicit UniformBlock(const std::string& name);
        void Init(const std::initializer_list<Element>& elements);
        virtual void UpdateOffset() = 0;

    protected:
        std::string _name;
        std::vector<Element> _uniformData;
        XXHashMap<std::string, int> _uniformOffsetMap;
        XXHashMap<std::string, int> _uniformSizeMap;
        int _totalSize = 0;
    };
}