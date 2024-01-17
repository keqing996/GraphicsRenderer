/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

namespace Renderer::Uniform
{
	enum class Name: int
	{
		MvpMatrices
	};
	
	class NameHelper
	{
	public:
		NameHelper() = delete;
		
	public:
		static std::string EnumToString(Name data);
		static std::optional<Name> StringToEnum(const std::string& data);
		
	};

}
