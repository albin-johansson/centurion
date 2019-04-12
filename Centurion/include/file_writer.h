#pragma once
#include <SDL_rwops.h>
#include <memory>
#include "file.h"

namespace centurion {
namespace io {

class FileWriter {
 private:
  std::unique_ptr<centurion::io::File> file;

 public:
  FileWriter();

  ~FileWriter();
};

}  // namespace io
}  // namespace centurion