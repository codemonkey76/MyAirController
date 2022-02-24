project "MyAir"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "myairpch.h"
	pchsource "src/myairpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/json/*.hpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.curl}",
		"%{IncludeDir.json}"
	}
	
	libdirs
	{
		"%{LibDir.curl}"
	}

	links
	{
		"libcurl_a",
		"Normaliz",
		"Ws2_32",
		"Wldap32",
		"Crypt32",
		"advapi32"
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