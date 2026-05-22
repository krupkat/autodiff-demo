cmake_minimum_required(VERSION 3.21)

project(AutoDiffDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11 xcursor xi)

add_library(sokol INTERFACE)
target_include_directories(sokol INTERFACE external/sokol)
target_link_libraries(sokol INTERFACE OpenGL::GL PkgConfig::X11)

add_library(imgui STATIC
  external/imgui/imgui.cpp
  external/imgui/imgui_draw.cpp
  external/imgui/imgui_demo.cpp
  external/imgui/imgui_tables.cpp
  external/imgui/imgui_widgets.cpp
)
target_include_directories(imgui PUBLIC external/imgui)

add_executable(autodiff_demo src/main.cpp)
target_link_libraries(autodiff_demo PRIVATE imgui sokol)
