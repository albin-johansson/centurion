# Centurion

Centurion is a small wrapper library for [SDL2](https://www.libsdl.org/index.php), written in C++. The main purpose of Centurion is to provide an object-oriented take on SDL2, which is originally a C library.

## Getting Started

### Prerequisites
Centurion is a wrapper library for SDL2, therefore you'll need to install SDL2 and its extension libraries before you can use Centurion.

The following are the versions of SDL that Centurion is based upon.
* [SDL2](https://www.libsdl.org/download-2.0.php)           version: 2.0.9
* [SDL2_image](https://www.libsdl.org/projects/SDL_image/)  version: 2.0.4
* [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)  version: 2.0.4
* [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)      version: 2.0.15

### Installing
Before you can start using Centurion, you'll need to download SDL2 and its extension libraries (SDL2_image, SDL2_mixer and SDL2_ttf). Use the links found under "prerequisites", and download the correct versions. 

### Using Centurion
All of the classes in Centurion reside in the `centurion` namespace. Furthermore, there are a number of subnamespaces.

* `centurion::visuals`
* `centurion::events`
* `centurion::visuals`
* `centurion::geo`
* `centurion::tools`

## Built With
- [Visual Studio 2017](https://visualstudio.microsoft.com/) - The IDE used

## Author

- **Albin Johansson** - *Software engineering student* - [GitHub](https://github.com/albin-johansson)

## Acknowledgments
- [Inspiration for README disposition](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
