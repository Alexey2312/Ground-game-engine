clear:
    rm -rf build

run:
    ./build/Ground

build:
    mkdir -p build
    cmake -B build -G Ninja
    cmake --build build
    ln -sf build/compile_commands.json compile_commands.json

debug-build:
    mkdir -p build
    cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
    ln -sf build/compile_commands.json compile_commands.json
