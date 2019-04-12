#pragma once
#include <SDL_rwops.h>
#include <memory>
#include <string>
#include "file.h"

namespace centurion {
namespace io {

class FileReader {
 private:
  centurion::io::File_uptr file;

 public:
  FileReader();

  ~FileReader();

  void ReadFile(const std::string path);

  // TODO how does the actual obtaining of data work?
};

}  // namespace io
}  // namespace centurion
