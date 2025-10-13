

## How to build

```bash
cmake -S. -Bbuild -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build -j$(nproc)
```

## How to run tests

```
./build/tests/all_tests
```
