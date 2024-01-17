/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

namespace Renderer
{
	enum class MaterialUniformVariableType: int
	{
		Int,
		Uint,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4
	};
	
	class MaterialUniformVariableTypeHelper
	{
	public:
		MaterialUniformVariableTypeHelper() = delete;
		
	public:
		static std::string EnumToString(MaterialUniformVariableType data);
		static std::optional<MaterialUniformVariableType> StringToEnum(const std::string& data);
		
	};

}
