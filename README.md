# centurion

[![version](https://img.shields.io/badge/version-5.3.0-blue.svg)](https://semver.org) 
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![CI: Windows](https://github.com/albin-johansson/centurion/actions/workflows/windows.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/windows.yml) 
[![CI: Ubuntu](https://github.com/albin-johansson/centurion/actions/workflows/ubuntu.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/ubuntu.yml) 
[![CI: MacOS](https://github.com/albin-johansson/centurion/actions/workflows/macos.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/macos.yml)
[![Documentation Status](https://readthedocs.org/projects/centurion/badge/?version=latest)](https://centurion.readthedocs.io/en/latest/?badge=latest)
[![codecov](https://codecov.io/gh/albin-johansson/centurion/branch/dev/graph/badge.svg)](https://codecov.io/gh/albin-johansson/centurion)

Centurion is a multimedia-library built on top of SDL2, written in modern C++, which provides abstractions for window-management, hardware-accelerated rendering, sound effects, music, game controllers, keyboard and mouse input, multi-threading, system information, etc. The aim of Centurion is to serve as an easy-to-use and intuitive alternative to raw SDL2, that provides much improved type- and memory-safety.

## Why Centurion?

Centurion is written in C++17, enabling far more expressive and intuitive APIs compared to plain C. For instance, Centurion performs automatic memory management and provides type safe APIs, which are designed to be hard to use incorrectly. However, Centurion is not just a wrapper library that mirrors the underlying SDL APIs. Instead, a lot of effort has been put into improving the APIs by making them utilise idiomatic modern C++.

## Documentation

The library features rich in-source documentation using Doxygen, which provides detailed information about the different APIs. The Doxygen documentation for the latest stable release is hosted [here](https://albin-johansson.github.io/centurion/). Furthermore, there's a Read-the-Docs site aimed to provide an overview of the library, with examples and some tips for using Centurion, which you can find [here](https://centurion.readthedocs.io/en/latest/).

## Installation

The library is distributed as a *single* header file, located in the `include` folder. Download the `centurion.hpp` header and include it in your project, and it's ready to be used! You will of course also need to install SDL2.

### Minimal program

```C++
#include <centurion.hpp>         // Amalgamated header, includes everything in the library!

int main(int argc, char** argv)  // The signature of main must be this!
{
  cen::library library;          // Initializes the library (i.e. SDL2, SDL2_image, SDL2_mixer and SDL_ttf)

  // The Centurion library is now ready to be used!

  return 0;
}
```

## Requirements

* C++17 or C++20
* SDL2 2.0.10, 2.0.12 or 2.0.14
* SDL2_image 2.0.5
* SDL2_ttf 2.0.4
* SDL2_mixer 2.0.4

## Relevant resources

* [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
* [SDL2 Wiki](https://wiki.libsdl.org/FrontPage)
* [SDL2](https://www.libsdl.org/index.php)
* [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
* [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
* [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
