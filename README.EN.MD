# Guic

GUIC (Graphical User Interface Creator) is a library for building graphical user interfaces. Guic lets you build interfaces without heavy frameworks and without deep knowledge of graphics APIs. The renderer is based on SDL.

**Version:** 0.2.0

Versioning follows SemVer 2.0.0 https://semver.org

## Documentation

- Russian: https://slideeex.github.io/Guic/ru/
- English: https://slideeex.github.io/Guic/en/

Feature stability labels are described on the "Stability labels" page in the "Public API" section: [ru](https://slideeex.github.io/Guic/ru/stability/), [en](https://slideeex.github.io/Guic/en/stability/).

## License

Guic is distributed under the GNU LGPL version 3 with additional permissions for linking and distribution. License texts are in the `Licenses/` folder of each build (`MinGW/Licenses`, `Visual Cpp/Licenses`, `Linux/Licenses`):

- `LICENSE`
- `COPYING`
- `ADDITIONAL_PERMISSIONS.md` - additional permissions
- `THIRD_PARTY_LICENSES.md` - third-party components

When distributing an archive, it must contain this folder.

## Builds

| Folder | Platform | Contents |
|---|---|---|
| `MinGW/x64` | Windows x64, MinGW | `guic.dll`, `guic-d.dll`, static libraries, headers |
| `MinGW/x32` | Windows x86, MinGW | `guic.dll`, `guic-d.dll`, static libraries, headers |
| `Visual Cpp/x64` | Windows x64, Visual C++ | `guic.dll`, `guic-d.dll`, `guic.lib`, `guic-d.lib`, `guic-s.lib`, `guic-s-d.lib`, headers |
| `Visual Cpp/x32` | Windows x86, Visual C++ | `guic.dll`, `guic-d.dll`, `guic.lib`, `guic-d.lib`, `guic-s.lib`, `guic-s-d.lib`, headers |
| `Linux/x64` | Linux x86_64 | `libguic.so`, `libguic.a`, headers |

`-d` in a name means a debug build.

`-s` in a name means a static build.

For Linux, x86 (32-bit) binaries are not provided. For other architectures and platforms, build the library from the sources in `Code/`.

For a program on Linux to find `libguic.so`, place the library next to the executable: the executable looks for it in its own folder. On Windows, `guic.dll` is also placed next to the `.exe`.

## Source code

- `Code/headers/` - public headers and internal engine headers.
- `Code/source/` - implementation.

## Example

`Tutorial/` contains `main.cpp` and a ready-made build of the example from the "Let's get started" section of the documentation.

## Third-party libraries

- SDL2 2.32.10 and SDL2_ttf 2.24.0 (zlib)
- FreeType 2.13.2 (FreeType License, FTL)
- HarfBuzz 8.1.1 (Old MIT)
- stb_image 2.30 (Public Domain)
- MaxRects (MaxRectsBinPack), Jukka Jylänki (Public Domain)

Copyright (C) 2026 V. Zaidov. The full list and license texts: `Licenses/THIRD_PARTY_LICENSES.md`.

## Bugs

Report bugs in Issues: [https://github.com/SlideeeX/Guic/issues](https://github.com/SlideeeX/Guic/issues)

## Roadmap

Plans, not promises: the order and scope may change.

- Renderer optimization: sorting images by size for the MaxRects atlas.
- An `Icon` class for loading SVG images.
- A container method for adding several elements at once.
- Extended window methods: enabling and disabling Drag and Drop, setting fullscreen mode, and similar proxy methods.
- Safe resource removal without undefined behavior.
- Output of errors, warnings and information from Guic.
