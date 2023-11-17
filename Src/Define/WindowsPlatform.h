#pragma once

#ifndef NOMINMAX
#   define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

namespace Renderer
{
    struct RhiOpenGLData
    {
        HDC _hDC;
        HGLRC _hRC;
    };
}
