with import <nixpkgs> { };

mkShell {
  packages = [
    # tools
    cmake
    clang-tools
    emscripten
    ninja
    pkgconf
    python3
    # libraries
    libGL.dev
    libx11.dev
    libxi.dev
    libxcursor.dev
    libxcb.dev
    libxdmcp.dev
    libxrender.dev
  ];
}
