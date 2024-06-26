/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#include "UniformName.h"
#include <unordered_map>
namespace Renderer::Uniform
{
	
	std::string NameHelper::EnumToString(Name data)
	{
		switch (data)
		{
			case Name::MvpMatrices: 
				return "MvpMatrices";
			default: 
				return "Unknown";
		}
		
	}
	
	std::optional<Name> NameHelper::StringToEnum(const std::string& data)
	{
		static std::unordered_map<std::string, Name> map = 
		{
			{ "MvpMatrices", Name::MvpMatrices },
		};
		
		if (map.contains(data))
			return map[data];
		
		return std::nullopt;
	}
	
}
