workspace "Fierce-Engine"
	architecture "x86_64"
	startproject "Engine"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["VULKAN"] = "C:/VulkanSDK/1.2.131.2/Include"
IncludeDir["DIRECTX_DXGI"] = "C:/Program Files (x86)/Windows Kits/10/Include/10.0.18362.0/shared"
IncludeDir["DIRECTX_CORE"] = "C:/Program Files (x86)/Windows Kits/10/Include/10.0.18362.0/um"
IncludeDir["EXTERNAL"] = "C:/Users/Tobias/Desktop/FierceEngineV1/external"

project "Fierce-Engine"
	location "Fierce-Engine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	defines
	{
		"VK_USE_PLATFORM_WIN32_KHR",
		"WIN32_LEAN_AND_MEAN",
		"_USE_MATH_DEFINES"
	}

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"%{prj.name}/**.ini",
		"%{prj.name}/**.vert",
		"%{prj.name}/**.frag",
		"%{prj.name}/**.spv",
		"%{prj.name}/shaders/CompileShaders.bat"
	}

	includedirs
	{
		"%{prj.name}",
		"%{IncludeDir.VULKAN}",
		"%{IncludeDir.DIRECTX_DXGI}",
		"%{IncludeDir.DIRECTX_CORE}",
		"%{IncludeDir.EXTERNAL}"
	}
	
	libdirs 
	{ 
		"C:/VulkanSDK/1.2.131.2/Lib",
		"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.18362.0/um/x64"
	}

	links 
	{ 
		"OpenGL32.lib",
		"vulkan-1.lib",
		"d3d12.lib",
		"dxgi.lib",
		"d3dcompiler.lib"
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "FIERCE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FIERCE_RELEASE"
		runtime "Release"
		optimize "on"