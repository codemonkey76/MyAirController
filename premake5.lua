include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "MyAir"
	architecture "x86_64"
	startproject "MyAirController"

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

group "Dependencies"
	include "vendor/premake"
	include "MyAirController/vendor/yaml-cpp"
group ""

include "MyAir"
include "MyAirController"