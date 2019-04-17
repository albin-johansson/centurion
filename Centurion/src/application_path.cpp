#include "application_path.h"
#include <SDL_filesystem.h>
#include <SDL_stdinc.h>
#include <string>

using std::string;

namespace centurion {
namespace tools {

ApplicationPath::ApplicationPath() {
  path_cstr = SDL_GetBasePath();
  path_cpp = string(path_cstr);
}

ApplicationPath::~ApplicationPath() { SDL_free(path_cstr); }

const string ApplicationPath::GetAbsolutePath() const noexcept {
  return path_cpp;
}

const string ApplicationPath::CreateRelativePath(const string& path) const
    noexcept {
  return string(path_cpp + path);
}

}  // namespace tools
}  // namespace centurion