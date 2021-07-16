# centurion

[![version](https://img.shields.io/badge/version-6.1.0-blue.svg)](https://semver.org)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![CI: Windows](https://github.com/albin-johansson/centurion/actions/workflows/windows.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/windows.yml)
[![CI: Ubuntu](https://github.com/albin-johansson/centurion/actions/workflows/ubuntu.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/ubuntu.yml)
[![CI: macOS](https://github.com/albin-johansson/centurion/actions/workflows/macos.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/macos.yml)
[![codecov](https://codecov.io/gh/albin-johansson/centurion/branch/dev/graph/badge.svg)](https://codecov.io/gh/albin-johansson/centurion)

Centurion is a multimedia-library built on top of SDL2, written in modern C++, which provides abstractions for window-management, hardware-accelerated rendering, sound effects, music, game controllers, keyboard and mouse input, multi-threading, system information, etc. The aim of Centurion is to serve as an easy-to-use and intuitive alternative to raw SDL2, that provides much improved type- and memory-safety.

The following table shows the supported versions of SDL2 and its extension libraries.

| Dependency            | Supported versions     |
| --------------------- | ---------------------- |
| SDL2                  | 2.0.10, 2.0.12, 2.0.14 |
| SDL2_image (Optional) | 2.0.5                  |
| SDL2_mixer (Optional) | 2.0.4                  |
| SDL2_ttf   (Optional) | 2.0.4                  |

## Why Centurion?

Centurion is written in C++17, enabling far more expressive and intuitive APIs compared to plain C. For instance, Centurion performs automatic memory management and provides type safe APIs, which are designed to be hard to use incorrectly. However, Centurion is not just a wrapper library that mirrors the underlying SDL APIs. Instead, a lot of effort has been put into improving the APIs by making them utilise idiomatic modern C++. Additionally, the library is continuously tested for correctness on Windows, Ubuntu and macOS, using unit tests, a mocked test suite and code coverage.

## Documentation

The library features rich in-source documentation using Doxygen, which provides detailed information about the different APIs. The Doxygen documentation for the latest stable release is hosted [here](https://albin-johansson.github.io/centurion/). Furthermore, refer to the [Wiki](https://github.com/albin-johansson/centurion/wiki) for additional information about the library.

## Installation

The library is distributed as a *single* header file, located in the `include` folder. Download the `centurion.hpp` header and include it in your project, and it's ready to be used! You will of course also need to install SDL2.

## Minimal Centurion program

The following is the smallest example of a Centurion program. All that is required to initialize the library is to create an instance of the `library` class, which must outlive the rest of your program, so it should be the first thing created in your `main` function.

```C++
#include <centurion.hpp>

int main(int argc, char** argv)
{
  cen::library centurion;

  // All SDL libraries are now initialized and ready to be used!

  return 0;
}
```
