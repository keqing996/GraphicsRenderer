#pragma once

#include <Helper/NonConstructible.h>
#include "UniformBuffer.h"

namespace Renderer
{
    class UniformFactory: Helper::NonConstructible
    {
    public:
        static Ptr<UniformBuffer> CreateMvpMatrices();
    };
}

