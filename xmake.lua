set_languages("c++23")
set_policy("build.c++.modules", true)

set_warnings("allextra", "error")

add_rules("mode.debug", "mode.release")
if is_mode("debug") then
    add_defines("DEBUG")
elseif is_mode("release") then
    add_defines("NDEBUG")
    set_optimize("fastest")
end

add_requires("raylib")

target("bpm")
    add_packages("raylib")
    set_kind("static")
    add_files("src/bpm.mpp")
    after_build(function (target)
        os.cp("data", target:targetdir())
    end)

target("test")
    add_deps("bpm")
    add_files("test/test.cpp")
