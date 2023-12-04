/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "UniformVariableType.h"
#include <unordered_map>
namespace Renderer
{
	
	std::string UniformVariableTypeHelper::UniformVariableTypeToString(UniformVariableType data)
	{
		switch (data)
		{
			case UniformVariableType::Int: 
				return "Int";
			case UniformVariableType::Float: 
				return "Float";
			case UniformVariableType::Mat3: 
				return "Mat3";
			case UniformVariableType::Mat4: 
				return "Mat4";
			case UniformVariableType::Texture2D: 
				return "Texture2D";
			default: 
				return "Unknown";
		}
		
	}
	
	std::optional<UniformVariableType> UniformVariableTypeHelper::StringToUniformVariableType(const std::string& data)
	{
		static std::unordered_map<std::string, UniformVariableType> map = 
		{
			{ "Int", UniformVariableType::Int },
			{ "Float", UniformVariableType::Float },
			{ "Mat3", UniformVariableType::Mat3 },
			{ "Mat4", UniformVariableType::Mat4 },
			{ "Texture2D", UniformVariableType::Texture2D },
		};
		
		if (map.contains(data))
			return map[data];
		
		return std::nullopt;
	}
	
}