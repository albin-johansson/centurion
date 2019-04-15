#pragma once
#include <SDL_rwops.h>
#include <memory>
#include <string>
#include "file.h"

namespace centurion {
namespace io {

/**
\since 1.1.0
*/
class FileReader {
 private:
  centurion::io::File_uptr file;

 public:
  FileReader();

  ~FileReader();

  void OpenFile(const std::string path);

  void OpenBinaryFile(const std::string path);

  template <class T>
  void Read(T target[], int nItems, int elementByteSize);

  // TODO how does the actual obtaining of data work?
};

}  // namespace io
}  // namespace centurion
