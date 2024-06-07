# Centurion

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![version](https://img.shields.io/github/v/release/albin-johansson/centurion)](https://github.com/albin-johansson/centurion/releases)
[![doxygen](https://img.shields.io/badge/doxygen-stable-blue)](https://albin-johansson.github.io/centurion/)
[![CI](https://github.com/albin-johansson/centurion/actions/workflows/ci.yml/badge.svg)](https://github.com/albin-johansson/centurion/actions/workflows/ci.yml)

## Introduction

Centurion is a modern C++ wrapper library for SDL3 that is intended to improve type-safety, memory safety and overall
ease-of-use. The aim is to provide intuitive and idiomatic C++ APIs that cover most of SDL3. The library has been
designed so that it's possible to mix SDL and Centurion, there's no lock-in.

Since version 8.0.0, Centurion requires at least C++20.

## Dependencies

The following table shows the supported versions of SDL3 and its extension libraries. Only the core SDL library is
mandatory. The extension libraries can be disabled at compile-time, by defining any of `CENTURION_NO_SDL_IMAGE`
, `CENTURION_NO_SDL_MIXER` or `CENTURION_NO_SDL_TTF`, respectively.

| Dependency | Source                                                                          | Supported versions |
|------------|---------------------------------------------------------------------------------|--------------------|
| SDL        | [www.libsdl.org](https://www.libsdl.org/download-3.0.php)                       | 3.0.0              |
| SDL_image* | [www.libsdl.org/projects/SDL_image](https://www.libsdl.org/projects/SDL_image/) | 3.0.0              |
| SDL_mixer* | [www.libsdl.org/projects/SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/) | 3.0.0              |
| SDL_ttf*   | [www.libsdl.org/projects/SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)     | 3.0.0              |

*Optional

## Installation

The library is intended to be used as a static library, all source files are located in the `lib` directory. Either
copy the source files directly into your project, or consume the library as a CMake target (just link against 
`centurion::centurion`). You will of course also need to install SDL3.

## Documentation

For additional documentation, see the [wiki](https://github.com/albin-johansson/centurion/wiki), hosted on GitHub.
