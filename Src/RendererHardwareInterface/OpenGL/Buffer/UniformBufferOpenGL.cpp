#include <Helper/Logger.h>

#include "Define/Define.h"
#include "UniformBufferOpenGL.h"
#include "Renderer/Uniform/UniformBlock.h"
#include "RendererHardwareInterface/OpenGL/Glad/Glad.h"

namespace Renderer
{
    static const umap<Uniform::Name, int> G_BingdPointMap {
        { Uniform::Name::MvpMatrices, 0 }
    };

    UniformBufferOpenGL::UniformBufferOpenGL(const Ptr<UniformBlock>& pBlock)
        : UniformBuffer(pBlock)
    {
        // get binding point
        auto blockName = pBlock->GetName();
        if (auto itr = G_BingdPointMap.find(blockName); itr != G_BingdPointMap.end())
            _bindingPoint = itr->second;
        else
        {
            Helper::Logger::LogError(std::format("Uniform block '{}' do not have binding point", static_cast<int>(blockName)));
            _bindingPoint = 0;
        }

        // create buffer
        ::glCreateBuffers(1, &_bufferId);
        ::glBindBuffer(GL_UNIFORM_BUFFER, _bufferId);
        ::glBufferData(GL_UNIFORM_BUFFER, _rawData.size(), _rawData.data(), GL_STATIC_DRAW);
        //::glBindBufferRange(GL_UNIFORM_BUFFER, _bindingPoint, _bufferId, 0, _rawData.size());
    }

    UniformBufferOpenGL::~UniformBufferOpenGL()
    {
        ::glDeleteBuffers(1, &_bufferId);
    }

    void UniformBufferOpenGL::Bind() const
    {
        ::glBindBuffer(GL_UNIFORM_BUFFER, _bufferId);
        ::glBindBufferBase(GL_UNIFORM_BUFFER, _bindingPoint, _bufferId);
    }

    void UniformBufferOpenGL::UnBind() const
    {
        ::glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UniformBufferOpenGL::CommitElementData(Uniform::Element name)
    {
        auto offset = _pUniformBlock->GetElementOffset(name);
        auto size = _pUniformBlock->GetElementSize(name);

        ::glBufferSubData(GL_UNIFORM_BUFFER, offset, size, _rawData.data() + offset);
    }

    void UniformBufferOpenGL::CommitBlockData()
    {
        ::glBufferData(GL_UNIFORM_BUFFER, _rawData.size(), _rawData.data(), GL_STATIC_DRAW);
    }
}
