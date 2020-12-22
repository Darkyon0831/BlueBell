project "ImGui"
    location "%{prj.name}/build"
    kind "StaticLib"    
    language "C++"
    files { "dependencies/imgui/*.h", "dependencies/imgui/*.cpp" }
    targetdir "%{prj.name}/bin/%{cfg.platform}/%{cfg.buildcfg}"
    targetname "%{prj.name}"
    objdir "%{prj.name}/bin/obj"

project "ShaderLib"

    location "%{prj.name}/build"

    kind "StaticLib"

    language "C++"

    includedirs { "dependencies/glslang/include", "dependencies/spirv-cross/include" }

    libdirs { "dependencies/glslang/lib", "dependencies/spirv-cross/lib/{cfg.buildcfg}"  }
    links { "GenericCodeGen", "glslang", "HLSL", "MachineIndependent", "OGLCompiler", "OSDependent", "SPIRV", "SPVRemapper", "spirv-cross-core", "spirv-cross-cpp", "spirv-cross-glsl", "spirv-cross-msl", "spirv-cross-reflect", "spirv-cross-util", "spirv-cross-hlsl" }

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    targetdir "%{prj.name}/bin/%{cfg.platform}/%{cfg.buildcfg}"
    targetname "%{prj.name}"
    objdir "%{prj.name}/bin/obj"