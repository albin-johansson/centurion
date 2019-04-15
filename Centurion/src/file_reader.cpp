#include "file_reader.h"
#include <stdio.h>

namespace centurion {
namespace io {

FileReader::FileReader() { file = nullptr; }

FileReader::~FileReader() = default;

void FileReader::OpenFile(const std::string path) {
  file = std::make_unique<File>(path);
}

void FileReader::OpenBinaryFile(const std::string path) {}

template <class T>
void FileReader::Read(T target[], int nItems, int elementByteSize) {
  
}

}  // namespace io
}  // namespace centurion