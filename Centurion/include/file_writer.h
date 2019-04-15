#pragma once
#include <SDL_rwops.h>
#include <memory>
#include "file.h"

namespace centurion {
namespace io {

/**
\since 1.1.0
*/
class FileWriter {
 private:
  centurion::io::File_uptr file;

 public:
  FileWriter();

  ~FileWriter();
};

}  // namespace io
}  // namespace centurion