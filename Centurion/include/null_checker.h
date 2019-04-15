#pragma once
#include <stdlib.h>

namespace centurion {
namespace tools {

/**
\brief The NullChecker class is a simple class that checks whether or not
pointers are null pointers.
\since 1.0.0
*/
class NullChecker {
 public:
  /**
  \brief Indicates whether the supplied pointer is a null pointer.
  */
  template <class T>
  inline static bool IsNull(T* arg) {
    return arg == nullptr || arg == NULL;
  }
};

}  // namespace tools
}  // namespace centurion