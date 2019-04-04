#include "font_factory.h"

using std::make_shared;
using std::shared_ptr;
using std::string;

namespace centurion {
namespace visuals {

shared_ptr<Font> FontFactory::CreateFont(const string& path, int size) {
  return make_shared<Font>(path, size);
}

}  // namespace visuals
}  // namespace centurion