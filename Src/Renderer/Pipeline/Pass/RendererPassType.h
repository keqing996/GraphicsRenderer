/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

namespace Renderer
{
	enum class RendererPassType: int
	{
		Forward,
		Shadow
	};
	
	class RendererPassTypeHelper
	{
	public:
		RendererPassTypeHelper() = delete;
		
	public:
		static std::string EnumToString(RendererPassType data);
		static std::optional<RendererPassType> StringToEnum(const std::string& data);
		
	};

}
