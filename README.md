# Centurion

[![version](https://img.shields.io/badge/version-6.2.0-blue.svg)](https://semver.org)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![doxygen](https://img.shields.io/badge/doxygen-stable-blue)](https://albin-johansson.github.io/centurion/)
[![CI: Windows](https://github.com/albin-johansson/centurion/actions/workflows/windows.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/windows.yml)
[![CI: Ubuntu](https://github.com/albin-johansson/centurion/actions/workflows/ubuntu.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/ubuntu.yml)
[![CI: macOS](https://github.com/albin-johansson/centurion/actions/workflows/macos.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/macos.yml)
[![codecov](https://codecov.io/gh/albin-johansson/centurion/branch/dev/graph/badge.svg)](https://codecov.io/gh/albin-johansson/centurion)

## Introduction

Centurion is a modern C++ wrapper library for SDL2 designed to improve type-safety, memory safety
and overall ease-of-use. The general aim of Centurion is to serve as an easy-to-use and intuitive
alternative to raw SDL2, by providing the same features whilst being safer and easier to use.
However, there are also aspects of the library that have no direct counterparts in SDL.

## Not Just a Wrapper Library

Centurion is not just a wrapper library! A lot of effort has been put into improving the SDL APIs by
utilising the full power of modern C++17 and C++20. Which has led to APIs that are far more
expressive and intuitive to use, compared to plain C.

## Features

The following is a (non-exhaustive) list of the features of Centurion.

* Window management
* Hardware-accelerated rendering (with basic support for OpenGL and Vulkan)
* TrueType font handling
* System events
* Keyboard input
* Mouse input
* Game controller and joystick input
* Force feedback
* Sound effects
* Music
* System information about platform, CPU, RAM, screen, battery, clipboard, counters, locale, etc.
* Filesystem information
* Cursor management
* Multi-threading utilities
* Message boxes

Additionally, many Centurion components feature serialization support based on the Cereal API,
string conversions, streaming support, etc. The library can be used with either C++17 or C++20, and
will use appropriate facilities depending on the language version used. For example, the library
will make use of `std::format`, if it is available.

## Dependencies

The following table shows the supported versions of SDL2 and its extension libraries. Only the core
SDL library is mandatory. The extension libraries can be disabled at compile-time, by defining any
of `CENTURION_NO_SDL_IMAGE`, `CENTURION_NO_SDL_MIXER` or `CENTURION_NO_SDL_TTF`, respectively.

| Dependency            | Source                                                                          | Supported versions     |
| --------------------- | ------------------------------------------------------------------------------- | ---------------------- |
| SDL2                  | [www.libsdl.org](https://www.libsdl.org/download-2.0.php)                       | 2.0.10, 2.0.12, 2.0.14 |
| SDL2_image (Optional) | [www.libsdl.org/projects/SDL_image](https://www.libsdl.org/projects/SDL_image/) | 2.0.5                  |
| SDL2_mixer (Optional) | [www.libsdl.org/projects/SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/) | 2.0.4                  |
| SDL2_ttf   (Optional) | [www.libsdl.org/projects/SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)     | 2.0.4                  |

## Installation

The library is distributed as a *single* header file, located in the `include` folder. Download
the `centurion.hpp` header and include it in your project, and it's ready to be used! You will of
course also need to install SDL2.

## Documentation

The Doxygen documentation for the latest stable release is
hosted [here](https://albin-johansson.github.io/centurion/). Furthermore, refer to
the [Wiki](https://github.com/albin-johansson/centurion/wiki) for additional information about the
library.

## Minimal Centurion program

The following is the smallest example of a Centurion program. All that is required to initialize the
library is to create an instance of the `library` class, which must outlive the rest of your
program, so it should be the first thing created in your `main` function.

```C++
#include <centurion.hpp>

int main(int argc, char** argv)
{
  cen::library centurion;

  // All SDL libraries are now initialized and ready to be used!

  return 0;
}
```
