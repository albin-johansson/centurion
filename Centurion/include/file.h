#pragma once
#include <SDL_rwops.h>
#include <memory>
#include <string>

namespace centurion {
namespace io {

class File final {
 private:
  SDL_RWops* file;
  const std::string path;

 public:
  explicit File(const std::string path);

  ~File();

  inline bool IsOpen() const { return file != nullptr; }
};

typedef std::shared_ptr<centurion::io::File> File_sptr;
typedef std::unique_ptr<centurion::io::File> File_uptr;
typedef std::weak_ptr<centurion::io::File> File_wptr;

}  // namespace io
}  // namespace centurion