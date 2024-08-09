workspace "Uncategorized"
   configurations { "Debug", "Release" }
   platforms { "Linux", "Windows" }
   location "build"

project "Uncategorized"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}_%{cfg.platform}"

   files { "src/**.h", "src/**.cpp" }

   filter "platforms:Windows"
      system "windows"
      systemversion "latest"
      defines { "PLATFORM_WINDOWS" }
      includedirs { "include/windows" }
      targetextension ".exe"

   filter "platforms:Linux"
      system "linux"
      defines { "PLATFORM_LINUX" }
      includedirs { "include/linux" }
      targetextension ".out"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
