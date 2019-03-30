#pragma once
#include <stdlib.h>
#include "centurion.h"

class centurion::tools::NullChecker {
 public:
  template <class T>
  static bool IsNull(T* arg) {
    return arg == nullptr || arg == NULL;
  }
};
