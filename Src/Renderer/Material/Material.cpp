#include "Material.h"
#include <fstream>
#include <Helper/Logger.h>

#include "nlohmann/json.hpp"
#include "Renderer/Shader/ShaderType.h"
#include "UniformVariable/MaterialUniformVariable.h"
#include "UniformVariable/MaterialUniformVariableNumeric.h"
#include "UniformVariable/MaterialUniformVariableType.h"

namespace Renderer
{
    class MaterialJsonHelper
    {
    public:
        static Ptr<MaterialUniformVariable> CreateUniformVar(const std::string& uniformBlockName, const std::string& uniformValueName, const nlohmann::basic_json<>& uniformVarConfig)
        {
            Ptr<MaterialUniformVariable> pUniVar = nullptr;

            const std::string& uniVarType = uniformVarConfig["Type"];
            if (uniVarType == MaterialUniformVariableTypeHelper::EnumToString(MaterialUniformVariableType::Int))
            {
                int value = uniformVarConfig["Value"];
                pUniVar = std::make_shared<MaterialUniformVariableNumeric<int>>(uniformBlockName, uniformValueName, value);
            }
            else if (uniVarType == MaterialUniformVariableTypeHelper::EnumToString(MaterialUniformVariableType::Uint))
            {
                unsigned int value = uniformVarConfig["Value"];
                pUniVar = std::make_shared<MaterialUniformVariableNumeric<unsigned int>>(uniformBlockName, uniformValueName, value);
            }
            else if (uniVarType == MaterialUniformVariableTypeHelper::EnumToString(MaterialUniformVariableType::Float))
            {
                float value = uniformVarConfig["Value"];
                pUniVar = std::make_shared<MaterialUniformVariableNumeric<float>>(uniformBlockName, uniformValueName, value);
            }
            else if (uniVarType == MaterialUniformVariableTypeHelper::EnumToString(MaterialUniformVariableType::Float2))
            {
                const float x = uniformVarConfig["X"];
                const float y = uniformVarConfig["Y"];
                pUniVar = std::make_shared<MaterialUniformVariableNumeric<Eigen::Vector2f>>(uniformBlockName, uniformValueName, Eigen::Vector2f { x, y });
            }
            else if (uniVarType == MaterialUniformVariableTypeHelper::EnumToString(MaterialUniformVariableType::Float3))
            {
                const float x = uniformVarConfig["X"];
                const float y = uniformVarConfig["Y"];
                const float z = uniformVarConfig["Z"];
                pUniVar = std::make_shared<MaterialUniformVariableNumeric<Eigen::Vector3f>>(uniformBlockName, uniformValueName, Eigen::Vector3f { x, y, z });
            }
            else if (uniVarType == MaterialUniformVariableTypeHelper::EnumToString(MaterialUniformVariableType::Float4))
            {
                const float x = uniformVarConfig["X"];
                const float y = uniformVarConfig["Y"];
                const float z = uniformVarConfig["Z"];
                const float w = uniformVarConfig["W"];
                pUniVar = std::make_shared<MaterialUniformVariableNumeric<Eigen::Vector4f>>(uniformBlockName, uniformValueName, Eigen::Vector4f { x, y, z, w });
            }

            return pUniVar;
        }
    };

    Material::Material(const std::string& materialPath)
    {
        std::ifstream fileStream(materialPath);
        if (!fileStream.is_open())
        {
            Helper::Logger::LogError("Get material fail: {}", materialPath);
            return;
        }

        nlohmann::json json;
        fileStream >> json;
        fileStream.close();

        for (const auto& [passName, passShaderConfig]: json.items())
        {
            auto pass = RendererPassTypeHelper::StringToEnum(passName);
            if (!pass.has_value())
            {
                Helper::Logger::LogError("Material pass error, {}, {}", materialPath, passName);
                continue;
            }

            auto pShader = ShaderProgram::Create();

            // vertex
            const std::string& vertexShaderTypeName = ShaderTypeHelper::EnumToString(ShaderType::Vertex);
            if (passShaderConfig.contains(vertexShaderTypeName))
            {
                auto vertexNode = passShaderConfig[vertexShaderTypeName];
                const std::string& shaderPath = vertexNode["Path"];
                pShader->AddShader<ShaderType::Vertex>(shaderPath);
            }

            // pixel
            const std::string& pixelShaderTypeName = ShaderTypeHelper::EnumToString(ShaderType::Pixel);
            if (passShaderConfig.contains(pixelShaderTypeName))
            {
                // attach shader
                auto pixelNode = passShaderConfig[pixelShaderTypeName];
                const std::string shaderPath = pixelNode["Path"];
                pShader->AddShader<ShaderType::Pixel>(shaderPath);
            }

            // uniform
            if (passShaderConfig.contains("UniformBlock"))
            {
                for (auto uniformBlockNode : passShaderConfig["UniformBlock"])
                {
                    const std::string& blockName = uniformBlockNode["BlockName"];
                    for (auto uniformValueNode : uniformBlockNode["Values"])
                    {
                        const std::string& varName = uniformValueNode["Name"];
                        auto pUniVar = MaterialJsonHelper::CreateUniformVar(blockName, varName, uniformValueNode);
                        if (pUniVar != nullptr)
                            _passUniVars[pass.value()].push_back(pUniVar);
                    }
                }
            }

            // textures
            if (passShaderConfig.contains("Textures"))
            {
                for (auto textureNode : passShaderConfig["Textures"])
                {
                    const std::string& uniVarName = textureNode["UniformVarName"];
                    const int slot = textureNode["Slot"];
                    const std::string& path = textureNode["Path"];

                    Ptr<MaterialTexture> pMatTex = std::make_shared<MaterialTexture>(uniVarName, slot, path);
                    _passTextures[pass.value()].push_back(pMatTex);
                }
            }

            pShader->Compile();
            _passShaderMap[pass.value()] = pShader;
        }
    }

    Ptr<ShaderProgram> Material::GetShader(RendererPassType pass) const
    {
        if (_passShaderMap.contains(pass))
            return _passShaderMap.at(pass);

        return nullptr;
    }

    const std::vector<Ptr<MaterialUniformVariable>>* Material::GetUniformVariables(RendererPassType pass) const
    {
        if (_passUniVars.contains(pass))
            return &_passUniVars.at(pass);

        return nullptr;
    }

    const std::vector<Ptr<MaterialTexture>>* Material::GetTextures(RendererPassType pass) const
    {
        if (_passTextures.contains(pass))
            return &_passTextures.at(pass);

        return nullptr;
    }
}
