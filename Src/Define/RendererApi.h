/* ****************************** 
 * Auto Generated File ! 
 * ******************************/

#pragma once

#include <string>
#include <optional>

enum class RendererApi: int
{
	OpenGL,
	Vulkan,
	D3D11,
	D3D12
};

class RendererApiHelper
{
public:
	RendererApiHelper() = delete;
	
public:
	static std::string EnumToString(RendererApi data);
	static std::optional<RendererApi> StringToEnum(const std::string& data);
	
};

