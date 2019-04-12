#pragma once
#include <SDL_rwops.h>
#include <memory>
#include "file.h"

namespace centurion {
namespace io {

class FileWriter {
 private:
  centurion::io::File_uptr file;

 public:
  FileWriter();

  ~FileWriter();
};

}  // namespace io
}  // namespace centurion