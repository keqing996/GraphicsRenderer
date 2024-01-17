/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

namespace Renderer
{
	enum class ShaderType: int
	{
		Vertex,
		Pixel,
		Count
	};
	
	class ShaderTypeHelper
	{
	public:
		ShaderTypeHelper() = delete;
		
	public:
		static std::string EnumToString(ShaderType data);
		static std::optional<ShaderType> StringToEnum(const std::string& data);
		
	};

}
