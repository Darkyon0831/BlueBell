project "ImGui"
    location "%{prj.name}/build"
    kind "StaticLib"    
    language "C++"
    files { "dependencies/imgui/*.h", "dependencies/imgui/*.cpp" }
    targetdir "%{prj.name}/bin/%{cfg.platform}/%{cfg.buildcfg}"
    targetname "%{prj.name}"
    objdir "%{prj.name}/bin/obj"

project "StarLab"

    location "%{prj.name}/build"

    kind "StaticLib"

    language "C++"

    includedirs { "dependencies/glslang/include", "dependencies/spirv-cross/include", "dependencies/hjson/include" }

    libdirs { "dependencies/glslang/lib/%{cfg.buildcfg}", "dependencies/spirv-cross/lib/%{cfg.buildcfg}", "dependencies/hjson/lib/%{cfg.buildcfg}"  }
    links { "spirv-cross-core", "spirv-cross-cpp", "spirv-cross-glsl", "spirv-cross-msl", "spirv-cross-reflect", "spirv-cross-util", "spirv-cross-hlsl", 
        "GenericCodeGen", "glslang", "glslang-default-resource-limits", "HLSL", "MachineIndependent", "OGLCompiler", "SPIRV", "OSDependent", "hjson" }

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    targetdir "%{prj.name}/bin/%{cfg.platform}/%{cfg.buildcfg}"
    targetname "%{prj.name}"
    objdir "%{prj.name}/bin/obj"