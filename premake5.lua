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

project "Little-Wooden-Engine"
	location "Little-Wooden-Engine"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LW_PLATFORM_WINDOWS",
			"LW_BUILD_DLL"
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
		}

	filter "configurations:Debug"
		defines "LW_DEBUG"
		symbols "On"
			
	filter "configurations:Release"
		defines "LW_DEBUG"
		optimize "On"

	filter "configurations:Dist"
		defines "LW_DEBUG"
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
		"Little-Wooden-Engine/vendor/spdlog/include",
		"Little-Wooden-Engine/src"
	}

	links
	{
		"Little-Wooden-Engine"
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
		defines "LW_DEBUG"
		symbols "On"
			
	filter "configurations:Release"
		defines "LW_DEBUG"
		optimize "On"

	filter "configurations:Dist"
		defines "LW_DEBUG"
		optimize "On"