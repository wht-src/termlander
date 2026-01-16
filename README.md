# Termlander

Terminal calendar with scheduling features. Early alpha.

## Building

You need `clang++` and `sqlite3`.

```bash
git clone https://github.com/wht-src/termlander
cd termlander
mkdir build 
cd build 
cmake .. # on windows, its recommended to install ninja and do cmake -G Ninja ..
cmake --build .
# you should see termlander binary in the build directory
```
