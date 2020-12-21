newoption {
    trigger = "gfxapi",
    value = "API",
    description = "Choose a particular 3D API for rendering",
    allowed = {
        { "d3d11",  "Direct3D 11 (Windows only)" }
    }
}

if not _OPTIONS["gfxapi"] then
    _OPTIONS["gfxapi"] = "d3d11"
end