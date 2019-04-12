#include "file.h"
#include <stdio.h>

namespace centurion {
namespace io {

File::File(const std::string path) : path(path) {
  // TODO What does "r+b" mean?
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

}  // namespace io
}  // namespace centurion