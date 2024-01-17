/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "MaterialUniformVariableType.h"
#include <unordered_map>
namespace Renderer
{
	
	std::string MaterialUniformVariableTypeHelper::EnumToString(MaterialUniformVariableType data)
	{
		switch (data)
		{
			case MaterialUniformVariableType::Int: 
				return "Int";
			case MaterialUniformVariableType::Uint: 
				return "Uint";
			case MaterialUniformVariableType::Float: 
				return "Float";
			case MaterialUniformVariableType::Float2: 
				return "Float2";
			case MaterialUniformVariableType::Float3: 
				return "Float3";
			case MaterialUniformVariableType::Float4: 
				return "Float4";
			case MaterialUniformVariableType::Mat3: 
				return "Mat3";
			case MaterialUniformVariableType::Mat4: 
				return "Mat4";
			default: 
				return "Unknown";
		}
		
	}
	
	std::optional<MaterialUniformVariableType> MaterialUniformVariableTypeHelper::StringToEnum(const std::string& data)
	{
		static std::unordered_map<std::string, MaterialUniformVariableType> map = 
		{
			{ "Int", MaterialUniformVariableType::Int },
			{ "Uint", MaterialUniformVariableType::Uint },
			{ "Float", MaterialUniformVariableType::Float },
			{ "Float2", MaterialUniformVariableType::Float2 },
			{ "Float3", MaterialUniformVariableType::Float3 },
			{ "Float4", MaterialUniformVariableType::Float4 },
			{ "Mat3", MaterialUniformVariableType::Mat3 },
			{ "Mat4", MaterialUniformVariableType::Mat4 },
		};
		
		if (map.contains(data))
			return map[data];
		
		return std::nullopt;
	}
	
}
