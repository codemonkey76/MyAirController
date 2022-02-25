project "MyAirController"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/MyAir/src",
		"%{IncludeDir.yaml_cpp}"
	}

	links
	{
		"MyAir",
		"yaml-cpp"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "MYAIR_DEBUG"
		runtime "Debug"
		symbols "on"
		

	filter "configurations:Release"
		defines "MYAIR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MYAIR_DIST"
		runtime "Release"
		optimize "on"
