# Centurion

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![version](https://img.shields.io/github/v/release/albin-johansson/centurion)](https://github.com/albin-johansson/centurion/releases)
[![CI](https://github.com/albin-johansson/centurion/actions/workflows/ci.yml/badge.svg)](https://github.com/albin-johansson/centurion/actions/workflows/ci.yml)

## Introduction

Centurion is a modern C++ wrapper library for SDL3 designed to improve type-safety, memory safety and overall
ease-of-use. The general aim of Centurion is to serve as an easy-to-use and intuitive alternative to raw SDL2, by
providing the same features while being safer and easier to use.

```C++
#include <centurion.hpp>

int main(int argc, char* argv[])
{
  const cen::sdl sdl;  // Init SDL
  const cen::img img;  // Init SDL_image
  const cen::mix mix;  // Init SDL_mixer
  const cen::ttf ttf;  // Init SDL_ttf

  cen::window window {"Centurion"};
  cen::renderer renderer = window.make_renderer();
  
  window.show();

  bool running = true;
  while (running) {
    cen::event_handler event;
    while (event.poll()) {
      if (event.is(cen::event_type::quit)) {
        running = false;
      }
    }

    renderer.clear_with(cen::colors::coral);
    renderer.present();
  }

  window.hide();
  return 0;
}
```

## Dependencies

The following table shows the supported versions of SDL3 and its extension libraries. Only the core SDL library is
mandatory. The extension libraries can be disabled at compile-time, by defining any of `CENTURION_NO_SDL_IMAGE`
, `CENTURION_NO_SDL_MIXER` or `CENTURION_NO_SDL_TTF`, respectively.

| Dependency            | Source                                                                              | Supported versions |
|-----------------------|-------------------------------------------------------------------------------------|--------------------|
| SDL3                  | [github.com/libsdl-org/SDL](https://github.com/libsdl-org/SDL/releases)             | 3.0.0              |
| SDL3_image (Optional) | [github.com/libsdl-org/SDL_image](https://github.com/libsdl-org/SDL_image/releases) | 3.0.0              |
| SDL3_mixer (Optional) | [github.com/libsdl-org/SDL_mixer](https://github.com/libsdl-org/SDL_mixer/releases) | 3.0.0              |
| SDL3_ttf   (Optional) | [github.com/libsdl-org/SDL_ttf](https://github.com/libsdl-org/SDL_ttf/releases)     | 3.0.0              |

## Installation

The library is distributed as a header-only library, which can be found in the `src` directory. Just download the
headers include them in your project, and the library it's ready to be used. You will of course also need to install
SDL3.

## Documentation

For additional documentation, see the [wiki](https://github.com/albin-johansson/centurion/wiki), hosted on GitHub.
