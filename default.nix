with import <nixpkgs> { };

mkShell {
  shellHook = ''
    export autodiff_ROOT="${autodiff}"
  '';

  packages = [
    # tools
    cmake
    clang-tools
    emscripten
    ninja
    pkgconf
    python3
    # libraries for sokol / imgui
    libGL.dev
    libx11.dev
    libxi.dev
    libxcursor.dev
    libxcb.dev
    libxdmcp.dev
    libxrender.dev
    # libraries
    autodiff
  ];
}
