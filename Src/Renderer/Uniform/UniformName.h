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
		static std::string NameToString(Name data);
		static std::optional<Name> StringToName(const std::string& data);
		
	};

}
