workspace "Phvika"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- GLFW submodule path
GLFW_DIR = "%{wks.location}/external/glfw"

-- GLFW project
project "GLFW"
    location "%{GLFW_DIR}"
    kind "StaticLib" -- or "SharedLib" if you want a dynamic library
    language "C"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{GLFW_DIR}/include/GLFW/glfw3.h",
        "%{GLFW_DIR}/include/GLFW/glfw3native.h",
        "%{GLFW_DIR}/src/**.c",
        "%{GLFW_DIR}/src/**.h"
    }
    
    includedirs
    {
        "%{GLFW_DIR}/include"
    }
    
    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        
        defines
        {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }
        
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"
        
    filter "configurations:Dist"
        defines "NDEBUG"
        optimize "On"

-- Your main project
project "Phvika"
    location "Phvika"
    kind "SharedLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/external/spdlog/include",
        "%{wks.location}/external/stb",
        "%{wks.location}/external/EASTL/include",
        "%{wks.location}/external/spdlog/include",
        "%{wks.location}/external/VulkanMemoryAllocator/include",
        "%{GLFW_DIR}/include", -- GLFW headers
        "%{wks.location}/external/EABase/include/Common"
    }
    
    links
    {
        "GLFW" -- Link against the GLFW project
    }
    
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        
        defines
        {
            "PHV_PLATFORM_WINDOWS",
            "PHV_BUILD_DLL"
        }
        
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Demo")
        }
        
    filter "configurations:Debug"
        defines "PHV_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "PHV_RELEASE"
        optimize "On"
        
    filter "configurations:Dist"
        defines "PHV_DIST"
        optimize "On"
        
project "Demo"
    location "Demo"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/external/spdlog/include",
        "Phvika/src",
        "%{wks.location}/external/stb",
        "%{wks.location}/external/EASTL/include",
        "%{wks.location}/external/spdlog/include",
        "%{wks.location}/external/VulkanMemoryAllocator/include",
        "%{GLFW_DIR}/include", -- GLFW headers
        "%{wks.location}/external/EABase/include/Common"
    }
    
    links
    {
        "Phvika",
        "GLFW" -- Link against the GLFW project
    }
    
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        
        defines
        {
            "PHV_PLATFORM_WINDOWS"
        }
        
    filter "configurations:Debug"
        defines "PHV_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "PHV_RELEASE"
        optimize "On"
        
    filter "configurations:Dist"
        defines "PHV_DIST"
        optimize "On"