/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

namespace Renderer::Uniform
{
	enum class Element: int
	{
		MvpMatricesModelMatrix,
		MvpMatricesViewMatrix,
		MvpMatricesProjectionMatrix
	};
	
	class ElementHelper
	{
	public:
		ElementHelper() = delete;
		
	public:
		static std::string EnumToString(Element data);
		static std::optional<Element> StringToEnum(const std::string& data);
		
	};

}
