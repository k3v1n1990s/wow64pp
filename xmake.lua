add_rules("mode.debug", "mode.release")
add_requires("gtest","xorstr")
target("test")
    set_languages("c++20")
    set_kind("binary")
    set_symbols("debug")
    add_files("test/*.cpp")
    add_includedirs("include")
    add_packages("gtest","xorstr")
    add_ldflags("/subsystem:console,5.01")
    after_build(function(target)
        os.exec(target:targetfile())
    end)