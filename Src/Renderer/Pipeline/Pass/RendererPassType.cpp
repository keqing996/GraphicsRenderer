/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "RendererPassType.h"
#include <unordered_map>
namespace Renderer
{
	
	std::string RendererPassTypeHelper::EnumToString(RendererPassType data)
	{
		switch (data)
		{
			case RendererPassType::Forward: 
				return "Forward";
			case RendererPassType::Shadow: 
				return "Shadow";
			default: 
				return "Unknown";
		}
		
	}
	
	std::optional<RendererPassType> RendererPassTypeHelper::StringToEnum(const std::string& data)
	{
		static std::unordered_map<std::string, RendererPassType> map = 
		{
			{ "Forward", RendererPassType::Forward },
			{ "Shadow", RendererPassType::Shadow },
		};
		
		if (map.contains(data))
			return map[data];
		
		return std::nullopt;
	}
	
}
