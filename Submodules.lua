project "ImGui"
    location "%{prj.name}/build"
    kind "StaticLib"    
    language "C++"
    files { "dependencies/imgui/*.h", "dependencies/imgui/*.cpp" }
    targetdir "%{prj.name}/bin/%{cfg.platform}/%{cfg.buildcfg}"
    targetname "%{prj.name}"
    objdir "%{prj.name}/bin/obj"