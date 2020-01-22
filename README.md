# Centurion ![Centurion](bin/centurion_icon.png) [![version](https://img.shields.io/badge/version-2.0.0-blue.svg)](https://semver.org) [![Build Status](https://travis-ci.org/albin-johansson/Centurion.svg?branch=master)](https://travis-ci.org/albin-johansson/Centurion) 


Centurion is a small wrapper library for [SDL2](https://www.libsdl.org/index.php), written in C++. The main purpose of Centurion is to provide a modern object-oriented take on SDL2, which is a C library. However, it's important to note that Centurion is __not__ meant to cover the entire SDL2 library. Instead, Centurion is designed to be used and compatible with native SDL2 enums, structs, etc.

## Getting Started

### Tools and dependencies
The following are the tools and dependencies used when developing the Centurion library.

* **SDL2** and all of its extension libraries (**SDL2_image**, **SDL2_mixer** and **SDL2_ttf**).
  The following are the versions of SDL that Centurion is based upon.
  * [SDL2](https://www.libsdl.org/download-2.0.php)           version: 2.0.10
  * [SDL2_image](https://www.libsdl.org/projects/SDL_image/)  version: 2.0.5
  * [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)  version: 2.0.4
  * [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)      version: 2.0.15
* [**Catch2**](https://github.com/catchorg/Catch2) for unit tests.
* [**GSL**](https://github.com/microsoft/GSL) (the Guidelines Support Library, implemented by Microsoft)
* **C++17**
* **GCC 8.1.0**
* **CMake 3.16.2**
* **CLion 2019.3.2**

### Installing Centurion
TODO...

### Using Centurion
All of the classes in Centurion reside in the `centurion` namespace.

Before you can start using components found in the Centurion library, you must initialise the library! Here's an example of how you would initialise and subsequently close the library.
```c++
// main.cpp

#include "centurion.h"

using namespace centurion;

static void run() {
  // ...
}

int main(int, char**) { // SDL2 requires this signature of main
  Centurion c;
  run();
  return 0;
}
```
## Author

- __Albin Johansson__ - _Software engineering student_ - [GitHub](https://github.com/albin-johansson)

## Acknowledgments
- [Inspiration for README disposition](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
