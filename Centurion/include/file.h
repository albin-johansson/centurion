#pragma once
#include <SDL_rwops.h>
#include <memory>
#include <string>
#include <vector>

namespace centurion {
namespace io {

/**
\since 1.1.0
*/
class File final {
 private:
  SDL_RWops* file;
  const std::string path;

 public:
  explicit File(const std::string path);

  ~File();

  /**
  \brief Reads the content of the file and stores it in the supplied vector.
  \since 1.1.0
  */
  template <class T>
  void Read(std::vector<T>& target);

  /**
  \brief Returns true if the file is open, returns false otherwise.
  \since 1.1.0
  */
  inline bool IsOpen() const { return file != nullptr; }
};

typedef std::shared_ptr<centurion::io::File> File_sptr;
typedef std::unique_ptr<centurion::io::File> File_uptr;
typedef std::weak_ptr<centurion::io::File> File_wptr;

}  // namespace io
}  // namespace centurion