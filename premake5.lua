dofile("PremakeArguments.lua")

workspace "BlueBell"
    configurations { "Debug", "Release" }
    platforms { "Win32", "x64" }

    defines { "BB_PLATFORM_WINDOWS", "NOMINMAX" }

    startproject "Sandbox"
    dependson { "BlueBell" }

    filter { "platforms:Win32" }
        system "Windows"
        architecture "x86"
        defines { "BB_32" }
    
    filter { "platforms:x64" }
        system "Windows"
        architecture "x86_64"
        defines { "BB_64" }

    filter "configurations:Debug"
        defines { "BB_DEBUG", "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "BB_RELEASE", "NDEBUG", "RELEASE" }
        optimize "On"

    project "BlueBell"

        location "%{prj.name}/build"

        includedirs { "dependencies/spdlog/include", "dependencies/imgui", "%{prj.name}/src", "StarLab/src", "dependencies/glslang/include", "dependencies/spirv-cross/include", "dependencies/hjson/include", "dependencies/DirectXTK/include", "dependencies/FBXSdk/include", "BlueFBX/src"  }

        kind "StaticLib"
        
        language "C++"

        libdirs { "ImGui/bin/%{cfg.platform}/%{cfg.buildcfg}", "StarLab/bin/%{cfg.platform}/%{cfg.buildcfg}", "dependencies/glslang/lib/%{cfg.buildcfg}", "dependencies/spirv-cross/lib/%{cfg.buildcfg}", "dependencies/hjson/lib/%{cfg.buildcfg}" }
        links { "ImGui" }

        files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

        targetdir "%{prj.name}/bin/%{cfg.platform}/%{cfg.buildcfg}"
        targetname "%{prj.name}"
        objdir "%{prj.name}/bin/obj"

        if _OPTIONS["gfxapi"] == "d3d11" then
            links { "d3d11", "DXGI", "D3DCompiler" }
            defines { "BB_D3D11" }
        end

    project "Sandbox"

        location "%{prj.name}/build"

        includedirs { "BlueBell/src", "dependencies/spdlog/include", "dependencies/imgui", "StarLab/src", "dependencies/glslang/include", "dependencies/spirv-cross/include", "dependencies/hjson/include", "dependencies/DirectXTK/include", "BlueFBX/src", "dependencies/FBXSdk/include" }

        kind "ConsoleApp"

        language "C++"

        libdirs { "BlueBell/bin/%{cfg.platform}/%{cfg.buildcfg}", "StarLab/bin/%{cfg.platform}/%{cfg.buildcfg}", "ImGui/bin/%{cfg.platform}/%{cfg.buildcfg}", "dependencies/glslang/lib/%{cfg.buildcfg}", "dependencies/spirv-cross/lib/%{cfg.buildcfg}", "dependencies/hjson/lib/%{cfg.buildcfg}", "BlueFBX/bin/%{cfg.platform}/%{cfg.buildcfg}", "dependencies/DirectXTK/lib/%{cfg.buildcfg}/%{cfg.platform}", "dependencies/FBXSdk/lib/%{cfg.platform}/%{cfg.buildcfg}" }
        links { "BlueBell", "ImGui", "StarLab", "DirectXTK", "libfbxsdk-md", "libxml2-md", "zlib-md", "BlueFBX" }

        files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

        targetdir "game"
        targetname "%{prj.name}_%{cfg.platform}_%{cfg.buildcfg}"
        objdir "%{prj.name}/bin/obj"

    -- Submodules
    dofile("Submodules.lua")

        