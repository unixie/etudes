# Etudes
Practicing and exploring programming


## Build

### Windows 11 (powershell)

|Name|                    Version|
|----|                    -------|
cmake|                   3.25.2
mingw-winlibs-llvm-ucrt| 12.2.0-16.0.0-10.0.0-r5
ninja|                   1.11.1

```powershell
$ cd <sub-project>
$ cmake -S . -G Ninja -B build
$ cmake --build build
$ .\build\apps\cli.exe --help
```


### Ubuntu 22.04 (zsh)

|Name|                    Version|
|----|                    -------|
cmake|                   3.22.1
Ubuntu clang | 14.0.0-1ubuntu1.1
ninja|                   1.10.1

```powershell
$ cd <sub-project>
$ cmake -S . -G Ninja -B build
$ cmake --build build
$ ./build/apps/cli --help
```

### Common
A `cpm-cache` directory is created on the top level for sharing between sub-directories.
Can be overridden by setting an env variable `CPM_SOURCE_CACHE`.

See `cmake/cpm-cache.cmake` for more details.

### README
See within each sub-directory.
