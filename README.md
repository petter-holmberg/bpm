# bpm

A simple C++23 multimedia library.

The intended purpose of this library is to provide a basic portable set of graphics, audio, and input handling primitives for quickly getting started with basic multimedia applications.

The library is very small and does not provide many advanced features. It is optimized for simplicity of use rather than performance or flexibility. Practical usage experience will guide the future evolution of the API.

Internally it uses the [raylib](https://www.raylib.com) library.

The [Noto Sans](https://fonts.google.com/noto/specimen/Noto+Sans), [Noto Sans Mono](https://fonts.google.com/noto/specimen/Noto+Sans+Mono), and [Noto Serif](https://fonts.google.com/noto/specimen/Noto+Sans) fonts are included with the library, with Noto Sans used as a default font for text.

## Build instructions

Uses [xmake](https://xmake.io). Builds a static library and a test application. Build with `xmake` and run the tests with `xmake run test`.

## API

See `test.cpp` for usage examples.
