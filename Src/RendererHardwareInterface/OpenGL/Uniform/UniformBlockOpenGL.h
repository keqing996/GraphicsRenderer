#pragma once

#include "Renderer/Uniform/UniformBlock.h"

namespace Renderer
{
    class UniformBlockOpenGL: public UniformBlock
    {
    public:
        explicit UniformBlockOpenGL(Uniform::Name name);

    public:
        void UpdateOffset() override;

    private:
        static constexpr int STD140_ALIGN = 16;
    };
}