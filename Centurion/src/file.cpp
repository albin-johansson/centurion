#include "file.h"
#include <stdio.h>

namespace centurion {
namespace io {

File::File(const std::string path) : path(path) {
  file = SDL_RWFromFile(path.c_str(), "r+b");
  if (file == nullptr) {
    printf("Failed to create file! Error: %s \n", SDL_GetError());
  }
}

File::~File() {
  if (file != nullptr) {
    SDL_RWclose(file);
  }
}

template <class T>
void File::Read(std::vector<T>& target) {
  T tmp[10];


  SDL_RWread(file, target, 10, 10);
}

}  // namespace io
}  // namespace centurion