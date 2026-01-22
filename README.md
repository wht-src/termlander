# Termlander

Coloured calendar with holidays.

## Building

You need `clang++` and `sqlite3`. It may work on Windows but only 
Linux builds are tested. In theory this can run on Windows.

```bash
git clone https://github.com/wht-src/termlander
cd termlander
mkdir release_build
cd release_build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

## Note

This program will use `~/.config/termlander/store.db3` to store the
holiday database.
