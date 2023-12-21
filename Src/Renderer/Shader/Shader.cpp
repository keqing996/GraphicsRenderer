#include "Shader.h"
#include "Util/Logger/Logger.h"
#include "Util/StringUtil.hpp"
#include "Application/Application.h"
#include <fstream>
#include <memory>

namespace Renderer
{

    void Shader::Load(const std::string& path)
    {
        std::string binPath = path;

        switch (Application::GetRenderApi())
        {
            case RendererApi::OpenGL:
                Util::StringOperation::Replace(binPath, std::string("/Shader/"), std::string("/ShaderBin/Spirv/"));
                binPath += ".spv";
                break;
            case RendererApi::Vulkan:
            case RendererApi::D3D11:
            case RendererApi::D3D12:
                break;
        }

        std::ifstream fs(binPath, std::ios::in | std::ios::binary);
        if (!fs.is_open())
        {
            Util::Logger::LogError("Get shader fail: {}", binPath);
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
}
