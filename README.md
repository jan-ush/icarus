# Icarus

## Build with vcpkg

Icarus uses vcpkg manifest mode to install Eigen3. Install and bootstrap
[vcpkg](https://github.com/microsoft/vcpkg), then set `VCPKG_ROOT` to the
vcpkg directory. Configure CMake with the vcpkg toolchain so the manifest
dependencies are installed automatically:

```sh
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build build
./build/icarus
```

On Windows PowerShell, use
`-DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"`.
