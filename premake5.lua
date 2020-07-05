workspace "Little-Wooden-Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "LittleWooden/vendor/GLFW/include"
IncludeDir["Glad"] = "LittleWooden/vendor/Glad/include"

include "LittleWooden/vendor/GLFW"
include "LittleWooden/vendor/Glad"

project "LittleWooden"
	location "LittleWooden"
	kind "SharedLib"
	language "C++"
		
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lwpch.hpp"
	pchsource "LittleWooden/src/lwpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LW_PLATFORM_WINDOWS",
			"LW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
		}

	filter "configurations:Debug"
		defines { "LW_DEBUG","LW_ENABLE_ASSERTS" }
		buildoptions "/MDd"
		symbols "On"
			
	filter "configurations:Release"
		defines "LW_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "LW_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
		
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"LittleWooden/vendor/spdlog/include",
		"LittleWooden/src"
	}

	links
	{
		"LittleWooden"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LW_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines { "LW_DEBUG","LW_ENABLE_ASSERTS" }
		buildoptions "/MDd"
		symbols "On"
			
	filter "configurations:Release"
		defines "LW_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "LW_DIST"
		buildoptions "/MD"
		optimize "On"
		