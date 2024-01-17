/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "UniformElement.h"
#include <unordered_map>
namespace Renderer::Uniform
{
	
	std::string ElementHelper::EnumToString(Element data)
	{
		switch (data)
		{
			case Element::MvpMatricesModelMatrix: 
				return "MvpMatricesModelMatrix";
			case Element::MvpMatricesViewMatrix: 
				return "MvpMatricesViewMatrix";
			case Element::MvpMatricesProjectionMatrix: 
				return "MvpMatricesProjectionMatrix";
			default: 
				return "Unknown";
		}
		
	}
	
	std::optional<Element> ElementHelper::StringToEnum(const std::string& data)
	{
		static std::unordered_map<std::string, Element> map = 
		{
			{ "MvpMatricesModelMatrix", Element::MvpMatricesModelMatrix },
			{ "MvpMatricesViewMatrix", Element::MvpMatricesViewMatrix },
			{ "MvpMatricesProjectionMatrix", Element::MvpMatricesProjectionMatrix },
		};
		
		if (map.contains(data))
			return map[data];
		
		return std::nullopt;
	}
	
}
