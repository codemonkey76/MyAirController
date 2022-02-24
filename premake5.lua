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

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
group ""

include "MyAir"
include "MyAirController"