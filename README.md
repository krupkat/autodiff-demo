# AutoDiff demo

## Build

```
cmake -B build . -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G Ninja
cmake --build build
```

## WebAssembly Build

```
emcmake cmake -B build-wasm . -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G Ninja
cmake --build build-wasm
```

Then serve the output directory and open `autodiff_demo.html` in a browser:

```
cd build-wasm && python3 -m http.server
```