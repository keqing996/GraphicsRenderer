/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

enum class ComponentType: int
{
	Camera,
	Light,
	Renderer
};

class ComponentTypeHelper
{
public:
	ComponentTypeHelper() = delete;
	
public:
	static std::string EnumToString(ComponentType data);
	static std::optional<ComponentType> StringToEnum(const std::string& data);
	
};

