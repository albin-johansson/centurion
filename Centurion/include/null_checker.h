#pragma once
#include <stdlib.h>

namespace centurion {
namespace tools {

/**
*DEPRECATED*
\brief The NullChecker class is a simple class that checks whether or not
pointers are null pointers.
\since 1.0.0
*/
class NullChecker {
 public:
  /**
  *DEPRECATED*
  \brief Indicates whether the supplied pointer is a null pointer.
  \since 1.0.0
  */
  template <class T>
  inline static bool IsNull(T* arg) noexcept {
    return arg == nullptr || arg == NULL;
  }
};

}  // namespace tools
}  // namespace centurion