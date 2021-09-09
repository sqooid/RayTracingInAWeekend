workspace "RayTracingInAWeekend"
	location ".."
	configurations { "Debug", "Release" }
	architecture "x86"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		objdir "../bin-int/Debug"
		targetdir "../bin/Debug"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		objdir "../bin-int/Release"
		targetdir "../bin/Release"

	filter {}

	includedirs {
		"../Dependencies/*/include",
	}

project "RayTracing"
	kind "ConsoleApp"
	location "../%{prj.name}"
	files {
		"../%{prj.name}/**.c",
		"../%{prj.name}/**.h",
		"../%{prj.name}/**.cpp",
		"../%{prj.name}/**.hpp",
	}
	includedirs{
		"../%{prj.name}/src",
		"../%{prj.name}/pch",
	}
	debugdir "../bin/Debug"
	pchheader "pch.h"
	pchsource "../%{prj.name}/pch/pch.cpp"
