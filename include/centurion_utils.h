#pragma once
#include <sstream>
#include <string>

namespace centurion {

/**
 * The CenturionUtils class provides utilities used by components of the Centurion library.
 *
 * @since 3.0.0
 */
class CenturionUtils final {
 public:
  CenturionUtils() = delete;

  /**
   * Returns a string that represents the memory address of the supplied pointer. The empty
   * string is returned if the supplied pointer is null.
   *
   * @tparam T the type of the pointer.
   * @param ptr the pointer that will be converted.
   * @return a string that represents the memory address of the supplied pointer.
   * @since 3.0.0
   */
  template<typename T>
  [[nodiscard]] static std::string address(T* ptr) {
    if (ptr) {
      std::ostringstream address;
      address << static_cast<void const*>(ptr);
      return address.str();
    } else {
      return "";
    }
  }
};

}
