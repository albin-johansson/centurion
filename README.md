# Centurion

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![version](https://img.shields.io/github/v/release/albin-johansson/centurion)](https://github.com/albin-johansson/centurion/releases)
[![doxygen](https://img.shields.io/badge/doxygen-stable-blue)](https://albin-johansson.github.io/centurion/)
[![CI: Windows](https://github.com/albin-johansson/centurion/actions/workflows/windows.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/windows.yml)
[![CI: Ubuntu](https://github.com/albin-johansson/centurion/actions/workflows/ubuntu.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/ubuntu.yml)
[![CI: macOS](https://github.com/albin-johansson/centurion/actions/workflows/macos.yml/badge.svg?branch=dev)](https://github.com/albin-johansson/centurion/actions/workflows/macos.yml)
[![codecov](https://codecov.io/gh/albin-johansson/centurion/branch/dev/graph/badge.svg)](https://codecov.io/gh/albin-johansson/centurion)

## Introduction

Centurion is a modern C++ wrapper library for SDL2 designed to improve type-safety, memory safety and overall
ease-of-use. The general aim of Centurion is to serve as an easy-to-use and intuitive alternative to raw SDL2, by
providing the same features whilst being safer and easier to use. However, there are also aspects of the library that
have no direct counterparts in SDL.

## Not Just a Wrapper Library

Centurion is not just a wrapper library! A lot of effort has been put into improving the SDL APIs by utilising the full
power of modern C++17 and C++20. Which has led to APIs that are far more expressive and intuitive to use, compared to
plain C.

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
* Compiler information

Additionally, many Centurion components feature serialization support based on the Cereal API, string conversions,
streaming support, etc. The library can be used with either C++17 or C++20, and will use appropriate facilities
depending on the language version used. For example, the library will make use of `std::format`, if it is available.

## Dependencies

The following table shows the supported versions of SDL2 and its extension libraries. Only the core SDL library is
mandatory. The extension libraries can be disabled at compile-time, by defining any of `CENTURION_NO_SDL_IMAGE`
, `CENTURION_NO_SDL_MIXER` or `CENTURION_NO_SDL_TTF`, respectively.

| Dependency            | Source                                                                          | Supported versions |
| --------------------- | ------------------------------------------------------------------------------- | ------------------ |
| SDL2                  | [www.libsdl.org](https://www.libsdl.org/download-2.0.php)                       | 2.0.10 ... 2.0.18  |
| SDL2_image (Optional) | [www.libsdl.org/projects/SDL_image](https://www.libsdl.org/projects/SDL_image/) | 2.0.5              |
| SDL2_mixer (Optional) | [www.libsdl.org/projects/SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/) | 2.0.4              |
| SDL2_ttf   (Optional) | [www.libsdl.org/projects/SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)     | 2.0.4              |

## Installation

The library is distributed in two flavours, either as a _single_ amalgamated `centurion.hpp` header
(located in the `include` folder), or simply as all the headers provided in the `src` folder. Just download the headers
include them in your project, and the library it's ready to be used! You will of course also need to install SDL2.

## Documentation

The Doxygen documentation for the latest stable release can be
found [here](https://albin-johansson.github.io/centurion/).

## Example

```C++
#include <centurion.hpp>

/* Note, the library provides an "SDL" namespace alias if you prefer that over "cen" */

int main(int, char**)
{
  /* Initialize SDL libraries */
  const cen::SDL_core sdl;
  const cen::SDL_image img;
  const cen::SDL_mixer mix;
  const cen::SDL_ttf ttf;
    
  cen::Window window{"Centurion"};
  cen::Renderer renderer{window};
  
  window.Show();
  
  bool running = true;
  while (running) {
    cen::Event event;
    while (event.Poll()) {
      if (event.Is<cen::QuitEvent>()) {
        running = false;
        break;
      }  
    }
    
    renderer.ClearWith(cen::colors::black);
    
    renderer.SetColor(cen::colors::red);
    renderer.FillRect(10, 10, 100, 50);
    
    renderer.Present();
  }
    
  window.Hide();
  return 0;
}

```
