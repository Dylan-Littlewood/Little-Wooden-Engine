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
IncludeDir["ImGui"] = "LittleWooden/vendor/imgui"

group "Dependencies"
	include "LittleWooden/vendor/GLFW"
	include "LittleWooden/vendor/Glad"
	include "LittleWooden/vendor/imgui"
group ""

project "LittleWooden"
	location "LittleWooden"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
		
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
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LW_PLATFORM_WINDOWS",
			"LW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\""
		}

	filter "configurations:Debug"
		defines { "LW_DEBUG","LW_ENABLE_ASSERTS" }
		symbols "On"
		runtime "Debug"
			
	filter "configurations:Release"
		defines "LW_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "LW_DIST"
		optimize "On"
		runtime "Release"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
		
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
		systemversion "latest"

		defines
		{
			"LW_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines { "LW_DEBUG","LW_ENABLE_ASSERTS" }
		symbols "On"
		runtime "Debug"
			
	filter "configurations:Release"
		defines "LW_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "LW_DIST"
		optimize "On"
		runtime "Release"
		