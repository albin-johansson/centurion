#pragma once
#include <memory>
#include <string>
#include "font.h"

namespace centurion {
namespace visuals {

class FontFactory final {
 private:
  FontFactory() = delete;

 public:
  ~FontFactory() = default;

  static std::shared_ptr<centurion::visuals::Font> CreateFont(
      const std::string& path, int size);
};

}  // namespace visuals
}  // namespace centurion