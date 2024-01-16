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
		static std::string ElementToString(Element data);
		static std::optional<Element> StringToElement(const std::string& data);
		
	};

}
