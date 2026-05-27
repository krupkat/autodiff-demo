cmake_minimum_required(VERSION 3.21)

project(AutoDiffDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(sokol INTERFACE)
target_include_directories(sokol INTERFACE external/sokol)

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

message(STATUS "System Name: ${CMAKE_SYSTEM_NAME}")

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  set_target_properties(autodiff_demo PROPERTIES SUFFIX ".html")

  target_link_options(autodiff_demo PRIVATE
    -sMAX_WEBGL_VERSION=2
    -sALLOW_MEMORY_GROWTH=1
    --shell-file ${CMAKE_SOURCE_DIR}/src/shell.html
  )
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  find_package(OpenGL REQUIRED COMPONENTS OpenGL)

  find_package(PkgConfig REQUIRED)
  pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11 xcursor xi)

  target_link_libraries(autodiff_demo PRIVATE OpenGL::GL PkgConfig::X11)
endif()
