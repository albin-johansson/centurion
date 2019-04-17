#pragma once
#include <string>

namespace centurion {
namespace tools {

/**
\brief The ApplicationPath class represents the file path of the application
executable. It's useful for things such as locating resources.
\since 1.0.0
*/
class ApplicationPath final {
 private:
  char* path_cstr = nullptr;
  std::string path_cpp;

 public:
  ApplicationPath();

  ~ApplicationPath();

  /**
  \brief Returns the absolute path of the application executable.
  \since 1.0.0
  */
  const std::string GetAbsolutePath() const noexcept;

  /**
  \brief Creates and returns a path based on the path of the application
  executable.
  \param path - the target path, relative to the application
  location.
  \since 1.0.0
  Example:
  Application location: ".../MyProjects/HelloWorld/app.exe"
  Relative path: "resources/image.png"
  CreateRelativePath( *Relative path* ) =>
  ".../MyProjects/HelloWorld/resources/image.png"
  */
  const std::string CreateRelativePath(const std::string& path) const noexcept;
};

}  // namespace tools
}  // namespace centurion