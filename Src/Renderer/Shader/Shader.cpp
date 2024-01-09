#include <fstream>
#include <sstream>
#include <memory>
#include <Helper/Logger.h>
#include <Helper/String.h>

#include "Shader.h"
#include "Application/Application.h"

namespace Renderer
{
    static bool SHADER_LOAD_FROM_BIN = true;

    void Shader::Load(const std::string& path)
    {
        std::string finalPath = path;

        if (SHADER_LOAD_FROM_BIN)
        {
            switch (Application::GetRenderApi())
            {
                case RendererApi::OpenGL:
                    Helper::String::Replace(finalPath, std::string("/Shader/"), std::string("/ShaderBin/Spirv/"));
                    finalPath += ".spv";
                    break;
                case RendererApi::Vulkan:
                case RendererApi::D3D11:
                case RendererApi::D3D12:
                    break;
            }

            std::ifstream fs(finalPath, std::ios::in | std::ios::binary);
            if (!fs.is_open())
            {
                Helper::Logger::LogError("Get shader fail: {}", finalPath);
                return;
            }

            fs.seekg(0, std::ios::end);
            unsigned int size = fs.tellg();

            std::unique_ptr<char[]> content(new char[size]);

            fs.seekg(0, std::ios::beg);
            fs.read(&content[0], size);
            fs.close();

            LoadFromBinaray(content.get(), size);
        }
        else
        {
            std::ifstream fs(finalPath, std::ios::in);
            if (!fs.is_open())
            {
                Helper::Logger::LogError("Get shader fail: {}", finalPath);
                return;
            }

            std::stringstream stringStream;
            stringStream << fs.rdbuf();
            LoadFromString(stringStream.str().c_str());
        }
    }
}
