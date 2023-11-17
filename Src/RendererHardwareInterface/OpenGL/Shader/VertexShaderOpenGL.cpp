#include "VertexShaderOpenGL.h"
#include "RendererHardwareInterface/OpenGL/GLAD/Glad.h"

namespace Renderer
{

    VertexShaderOpenGL::~VertexShaderOpenGL()
    {
        ::glDeleteShader(_shaderId);
    }

    bool VertexShaderOpenGL::LoadFromString(const char* data)
    {
        _shaderId = ::glCreateShader(GL_VERTEX_SHADER);
        ::glShaderSource(_shaderId, 1, &data, nullptr);
        return true;
    }

    bool VertexShaderOpenGL::Compile()
    {
        ::glCompileShader(_shaderId);
        GLint vsSuccess = false;
        ::glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &vsSuccess);
        return vsSuccess;
    }

    unsigned int VertexShaderOpenGL::GetShaderId() const
    {
        return _shaderId;
    }
}