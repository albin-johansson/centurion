#pragma once
#include <SDL.h>

namespace centurion {

/**
 * The BoolConverter class is a service for converting C++ boolean values to the
 * corresponding SDL_bool enum values.
 *
 * @since 3.0.0
 */
class BoolConverter final {
 public:
  BoolConverter() = delete;

  ~BoolConverter() noexcept = default;

  /**
   * Returns the corresponding SDL_bool value for the supplied boolean value.
   *
   * @param b the boolean value that will be converted.
   * @return the corresponding SDL_bool value for the supplied boolean value.
   * @since 3.0.0
   */
  [[nodiscard]]
  inline static constexpr SDL_bool convert(bool b) noexcept {
    return b ? SDL_TRUE : SDL_FALSE;
  }
};

}