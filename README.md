# Centurion

Centurion is a small wrapper library for [SDL2](https://www.libsdl.org/index.php), written in C++. The main purpose of Centurion is to provide an object-oriented take on SDL2, which is originally a C library.

## Getting Started

### Dependencies
* **SDL2** and all of its extension libraries (**SDL2_image**, **SDL2_mixer** and **SDL2_ttf**).
  The following are the versions of SDL that Centurion is based upon.
  * [SDL2](https://www.libsdl.org/download-2.0.php)           version: 2.0.9
  * [SDL2_image](https://www.libsdl.org/projects/SDL_image/)  version: 2.0.4
  * [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)  version: 2.0.4
  * [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)      version: 2.0.15
* **Windows 10**. Although Centurion might work with older versions such as Windows 7.
* **[Visual Studio 2017](https://visualstudio.microsoft.com/)** (should work with other versions). If you'd like to use Centurion   outside of Visual Studio, you'll have to compile the library by yourself.

### Installing (for Visual Studio 2017)
If you haven't got SDL2, you'll need to download SDL2 and its extension libraries (SDL2_image, SDL2_mixer and SDL2_ttf). Use the links found under "prerequisites", and download the correct versions. The following images show the download links that you should use. 

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

When you're done downloading, unzip the folders and put them wherever you see fit. You might want to transfer the contents of the `include` and `lib` folders from the extension libraries to the respective folders in the main SDL2 folder (if you do, please make sure not to mix the `x86` and `x64` files). However, the important thing is that you know where they are. 

**TODO finish the installation tutorial...**

### Using Centurion
All of the classes in Centurion reside in the `centurion` namespace. Furthermore, there are a number of subnamespaces.

* `centurion::visuals`
* `centurion::events`
* `centurion::visuals`
* `centurion::geo`
* `centurion::tools`

Before you can start using components found in the Centurion library, you must initialize the library! Here's an example of how you would initialize and then deinitialize the library.
```c++
#include "centurion.h"

using centurion::Centurion;

int main(int argv, char** argc) 
{
    Centurion::Init();
    
    // Your code goes here!
    
    Centurion::Close();
    return 0;
}
```
## Author

- **Albin Johansson** - *Software engineering student* - [GitHub](https://github.com/albin-johansson)

## Acknowledgments
- [Inspiration for README disposition](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
