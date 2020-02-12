/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_CENTURION_UTILS_HEADER
#define CENTURION_CENTURION_UTILS_HEADER

#include <memory>
#include <sstream>
#include <string>

#include "centurion_api.h"

namespace centurion {

/**
 * The CenturionUtils class provides utilities used by components of the
 * Centurion library.
 *
 * @since 3.0.0
 */
class CenturionUtils final {
 public:
  CenturionUtils() = delete;

  /**
   * Returns a string that represents the memory address of the supplied
   * pointer. The empty string is returned if the supplied pointer is null.
   *
   * @tparam T the type of the pointer.
   * @param ptr the pointer that will be converted.
   * @return a string that represents the memory address of the supplied
   * pointer.
   * @since 3.0.0
   */
  template <typename T>
  CENTURION_NODISCARD static std::string address(T* ptr) {
    if (ptr) {
      std::ostringstream address;
      address << static_cast<void const*>(ptr);
      return address.str();
    } else {
      return "";
    }
  }
};

#ifndef CENTURION_HAS_MAKE_UNIQUE

/**
 * Creates and returns a unique pointer. This method should only be used when
 * C++11 is used, since it doesn't provide std::make_unique.
 *
 * @tparam T the type of the object that will be created.
 * @tparam Args the type of the arguments that will be passed to an appropriate
 * constructor.
 * @param args the arguments that will be passed to an appropriate constructor.
 * @return a unique pointer.
 * @since 3.2.0
 */
template <typename T, typename... Args>
CENTURION_NODISCARD std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif

}  // namespace centurion

#endif  // CENTURION_CENTURION_UTILS_HEADER