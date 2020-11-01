workspace "Little-Wooden-Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "LittleWooden/vendor/GLFW/include"
IncludeDir["Glad"] = "LittleWooden/vendor/Glad/include"
IncludeDir["ImGui"] = "LittleWooden/vendor/imgui"
IncludeDir["glm"] = "LittleWooden/vendor/glm"
IncludeDir["stb_image"] = "LittleWooden/vendor/stb_image"

group "Dependencies"
	include "LittleWooden/vendor/GLFW"
	include "LittleWooden/vendor/Glad"
	include "LittleWooden/vendor/imgui"
group ""

project "LittleWooden"
	location "LittleWooden"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lwpch.hpp"
	pchsource "LittleWooden/src/lwpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LW_PLATFORM_WINDOWS",
			"LW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "LW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LW_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"LittleWooden/vendor/spdlog/include",
		"LittleWooden/src",
		"LittleWooden/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"LittleWooden"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LW_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "LW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LW_DIST"
		runtime "Release"
		optimize "on"
