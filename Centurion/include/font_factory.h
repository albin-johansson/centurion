#pragma once
#include <memory>
#include <string>
#include "font.h"

namespace centurion {
namespace visuals {

/**
* DEPRECATED *
\brief The FontFactory class is a factory for creating instances of the Font
class.
\since 1.0.0
*/
class FontFactory final {
 private:
  FontFactory() = delete;

 public:
  ~FontFactory() = default;

  /**
  \brief Creates and returns a Font instance.
  \param path - the path of the font file. The file must have the
  .TTF-extension.
  \param size - the desired font size.
  \since 1.0.0
  */
  static std::shared_ptr<centurion::visuals::Font> CreateFont(
      const std::string& path, int size);
};

}  // namespace visuals
}  // namespace centurion