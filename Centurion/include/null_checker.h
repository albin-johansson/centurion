#pragma once
#include <stdlib.h>

namespace centurion {
namespace tools {

class NullChecker {
 public:
  template <class T>
  static bool IsNull(T* arg) {
    return arg == nullptr || arg == NULL;
  }
};

}  // namespace tools
}  // namespace centurion