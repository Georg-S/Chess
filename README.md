# Chess engine + Application
A chess engine library written in C++ and an application that uses the engine.

![Chess](/Images/Readme.png)

## Build

### Complete

To build the complete project for windows you need to have the SDL2 and SDL2 image library.

Add the following environment variables (pointing to the corresponding folders):

* SDL2_INCLUDE
* SDL2_BIN
* SDL2IMAGE_INCLUDE
* SDL2IMAGE_BIN

After that, run the cmak_build.bat and now the solution can be oppened in the build folder.

## Engine only

For only the engine, no library is required.
Go in the uppermost CMakeLists.txt and comment out the line "add_subdirectory(application)"
After that, run the cmak_build.bat and now the solution can be oppened in the build folder.

## Sources

- https://www.chessprogramming.org/
- https://peterellisjones.com/posts/generating-legal-chess-moves-efficiently/
- https://sites.google.com/site/numptychess/perft
- https://rustic-chess.org/
