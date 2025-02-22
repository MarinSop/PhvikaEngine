workspace "Phvika"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include other project files
include "external/glfw/premake5.lua"
include "Phvika/premake5.lua"
include "Demo/premake5.lua"
include "external/EASTL/premake5.lua"
