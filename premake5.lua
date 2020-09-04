workspace "asteroids"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "asteroids"

	flags
	{
		"MultiProcessorCompile"
	}

build_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Core/"
project "asteroids"
	location "asteroids"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	
	targetdir ("bin/" .. build_dir .. "/%{prj.name}")
	objdir ("bin-int/" .. build_dir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.hpp", 
			"%{prj.name}/src/**.c", "%{prj.name}/src/**.cpp" }

	includedirs { "%{prj.name}/src",  "%{wks.location}/vendor/freeglut/include"}

	links {
		"freeglut.lib",
		"glu32",
		"opengl32.lib"
	}

	libdirs { "%{wks.location}/vendor/freeglut/lib/x64"}

	filter "configurations:Debug"
		defines { "AST_CONFIG_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "AST_CONFIG_RELEASE" }
		optimize "On"

	filter "system:windows"
		systemversion "latest"
		defines { "AST_SYSTEM_WINDOWS" }

		postbuildcommands
		{
			("{COPY} %{wks.location}/vendor/freeglut/bin/x64 ../bin/" .. build_dir .. "/asteroids")
		}

	filter "system:linux"
		defines { "AST_SYSTEM_LINUX" }

	filter "system:macosx"
		defines { "AST_SYSTEM_MACOSX" }
