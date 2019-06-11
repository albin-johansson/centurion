# Centurion [![version](https://img.shields.io/badge/version-2.0.0-blue.svg)](https://semver.org)


Centurion is a small wrapper library for [SDL2](https://www.libsdl.org/index.php), written in C++. The main purpose of Centurion is to provide an object-oriented take on SDL2, which is originally a C library. However, it's important to note that Centurion is __not__ meant to cover the entire SDL2 library, but instead Centurion is designed to be used alongside with SDL2.

## Getting Started

### Dependencies
* **SDL2** and all of its extension libraries (**SDL2_image**, **SDL2_mixer** and **SDL2_ttf**).
  The following are the versions of SDL that Centurion is based upon.
  * [SDL2](https://www.libsdl.org/download-2.0.php)           version: 2.0.9
  * [SDL2_image](https://www.libsdl.org/projects/SDL_image/)  version: 2.0.4
  * [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)  version: 2.0.4
  * [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)      version: 2.0.15
* **Windows**. 
* **[Visual Studio 2019](https://visualstudio.microsoft.com/)** (should work with other versions). If you'd like to use Centurion   outside of Visual Studio, you'll have to compile the library by yourself.

### Installing Centurion (with Visual Studio 2017)
If you haven't got SDL2, you'll need to download SDL2 and its extension libraries (SDL2_image, SDL2_mixer and SDL2_ttf). Use the links found under __dependencies__, and download the correct versions. The following images show the download links that you should use. 

<p align="center">
<img src="/readme-files/centurion_sdl2_link.PNG" alt="" width="350">
</p>  

<p align="center">
<img src="/readme-files/centurion_image_link.PNG" alt="" width="350">
</p>

<p align="center">
<img src="/readme-files/centurion_ttf_link.PNG" alt="" width="350">
</p>

<p align="center">
<img src="/readme-files/centurion_mixer_link.PNG" alt="" width="350">
</p>

When you're done downloading, unzip the folders and put them wherever you see fit. You might want to transfer the contents of the `include` and `lib` folders from the extension libraries to the respective folders in the main SDL2 folder (if you do, please make sure not to mix the `x86` and `x64` files). The important thing is that you know where they are. After you've successfully downloaded SDL, go ahead and download the `include` and `lib` folders from Centurion.

When you've created and set up your project/solution in Visual Studio, you'll need to specify your dependencies. 
1. Navigate to the `properties` window for your project (right click your project in the solution explorer).
0. Make sure that the `Configuration` combo box is set to `All Configurations`.
0. Make sure that the `Platform` combo box is set to `All Platforms`.
0. Click the `C/C++` tab.
0. Fill in the option called `Additional Include Directories` so that it contains the paths to the `include` folders in __all__ of the external libraries.
0. Click the `Linker` tab.
0. Click the `General` tab.
0. Fill in the option called `Additional Library Directories` so that it contains the paths to __all__ of the `lib` folders of the external libraries.
0. It's __very important__ to use the correct configuration and platform settings when changing the `Additional Library Directories` option. Make sure that the `Configuration` and `Platform` settings match the `lib` folder that you choose. 
0. Click the `Input` tab, which is also located under the `Linker` tab.
0. Fill in the option called `Additional Dependencies`. It should contain `SDL2.lib`, `SDL2main.lib`, `SDL2_image.lib`, `SDL2_mixer.lib`, `SDL2_ttf.lib` and `Centurion.lib`.
0. Click the `System` tab, also located under the `Linker` tab.
0. Fill in the `SubSystem` option with either `Console` or `Windows`. If you choose the `Console` option, a console will open every time you run your program. 
0. You're all set! You should now be able to include SDL and Centurion components.

### Using Centurion
All of the classes in Centurion reside in the `centurion` namespace. Furthermore, there are a number of subnamespaces.

* `centurion::visuals` - contains components mainly related to visuals such as windows and renderers.
* `centurion::events` - contains components related to various forms of input such as the keyboard and mouse.
* `centurion::input` - contains input components that are state based (and not event based).
* `centurion::geo` - contains components related to geometry such as rectangles and points.
* `centurion::audio` - contains audio components related to both music and sound effects.
* `centurion::tools` - contains various useful tools, not necessarily related to the SDL library.

Before you can start using components found in the Centurion library, you must initialize the library! Here's an example of how you would initialize and subsequently deinitialize the library.
```c++
#include <centurion_everything.h>

using centurion::Centurion;

void Foo() {
  // ...
}

int main(int argv, char** argc) {
  Centurion::Init();
  Foo();
  Centurion::Close();
  return 0;
}
```
## Author

- __Albin Johansson__ - _Software engineering student_ - [GitHub](https://github.com/albin-johansson)

## Acknowledgments
- [Inspiration for README disposition](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
