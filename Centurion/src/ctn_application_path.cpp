#include "ctn_application_path.h"
#include <SDL_filesystem.h>
#include <SDL_stdinc.h>

namespace centurion {
namespace tools {

ApplicationPath::ApplicationPath() {
  path_cstr = SDL_GetBasePath();
  path_cpp = std::string(path_cstr);
}

ApplicationPath::~ApplicationPath() { SDL_free(path_cstr); }

const std::string ApplicationPath::GetAbsolutePath() const noexcept {
  return path_cpp;
}

const std::string ApplicationPath::CreateRelativePath(
    const std::string& path) const noexcept {
  return std::string(path_cpp + path);
}

ApplicationPath_sptr ApplicationPath::CreateShared() {
  return std::make_shared<ApplicationPath>();
}

ApplicationPath_uptr ApplicationPath::CreateUnique() {
  return std::make_unique<ApplicationPath>();
}

ApplicationPath_wptr ApplicationPath::CreateWeak() { return CreateShared(); }

}  // namespace tools
}  // namespace centurion