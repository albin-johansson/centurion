# <img src="meta/centurion.png" alt="Centurion" width="200"/> [![version](https://img.shields.io/badge/version-5.0.0-magenta.svg)](https://semver.org) [![Build Status](https://travis-ci.org/albin-johansson/Centurion.svg?branch=master)](https://travis-ci.org/albin-johansson/Centurion) [![codecov](https://codecov.io/gh/albin-johansson/Centurion/branch/master/graph/badge.svg)](https://codecov.io/gh/albin-johansson/Centurion) [![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) ![GitHub commit activity](https://img.shields.io/github/commit-activity/m/albin-johansson/Centurion) ![GitHub repo size](https://img.shields.io/github/repo-size/albin-johansson/Centurion) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## What is Centurion?

Centurion is a modern C++ library built on top of SDL2 in order to improve type-safety, memory safety and overall ease-of-use. It can be used for creating windows, 2D-rendering, keyboard input, mouse input, sound effects, music, etc. In other words, most of the things you can do with SDL2. In addition to this, all Centurion components are built to support being used alongside the SDL2 components so that you can use SDL2 for the things that Centurion doesn't cover.

## Why use Centurion?

Centurion is written in modern C++17 and as such is much more intuitive and easy to use that raw SDL2, which is written in C. No need to worry about memory leaks and ownership of resources! By using Centurion you will write code that is type-safe, clear and efficient.

## How do I install Centurion?

There are two ways of installing the Centurion library in your project.

- You can simply link against Centurion as a shared library, just like you would with any other library. This is the recommended approach for using the Centurion library.

- You can use the library as a pseudo-"header-only" library, by defining the macro `CENTURION_HEADER_ONLY` in the file `centurion_cfg.h`. Note that you'll need to include the `.cpp` files as well if you want to go for this option.
  
Since Centurion is built on top of SDL2, you'll need to install SDL2! In order to be able use everything in Centurion, you'll need to install SDL2, SDL2_image, SDL2_ttf and SDL2_mixer. Don't worry! It's easy when you get the hang of it. Furthermore, Centurion comes bundled with two dependencies, `gsl-lite` and `optional`.

## How do I use Centurion?

Before you can get started with using the Centurion components, you must initialize the library. Here's how to do just that. Refer the in-source documentation or generated Doxygen documentation for more information about the library. :closed_book:

```C++
#include <centurion_as_ctn.hpp>

int main(int, char**)
{
  ctn::centurion_lib c;
  // Start using Centurion!
}
```

Happy coding! :heart:

## Author

- __Albin Johansson__ - _Software engineering student_ - [GitHub](https://github.com/albin-johansson)