project "Phvika"
    location "%{wks.location}/Phvika"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")
    
    buildoptions { "/utf-8" }

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "%{wks.location}/external/spdlog/include",
        "%{wks.location}/external/stb",
        "%{wks.location}/external/EASTL/include",
        "%{wks.location}/external/VulkanMemoryAllocator/include",
        "%{wks.location}/external/glfw/include",
        "%{wks.location}/external/EABase/include/Common",
        "$(VULKAN_SDK)/Include"
    }

    libdirs
    { 
        "$(VULKAN_SDK)/Lib" 
    }
    
    links
    {
        "GLFW",
        "EASTL",
        "vulkan-1"
    }
    
    filter "system:windows"
        staticruntime "On"
        systemversion "latest"
        
        defines
        {
            "PHV_PLATFORM_WINDOWS",
            "PHV_BUILD_DLL",
            "PHV_ENABLE_ASSERT"
        }
        
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/" .. outputdir .. "/Demo")
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
