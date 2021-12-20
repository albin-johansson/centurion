#ifndef CENTURION_SDL_STRING_HPP_
#define CENTURION_SDL_STRING_HPP_

#include <SDL.h>

#include <memory>  // unique_ptr
#include <string>  // string

#include "../detail/sdl_deleter.hpp"
#include "../common.hpp"

namespace cen {

/**
 * \brief Represents an SDL string.
 *
 * \details Certain SDL APIs return `char*` strings that need to be freed using
 * `SDL_free()`, this class serves as a small wrapper around such strings. Use the `copy()`
 * member function to convert the string into a corresponding `std::string`.
 *
 * \note Instances of `sdl_string` might manage null strings. Use the overloaded `operator
 * bool()` in order to determine whether or not any associated string is null.
 */
class sdl_string final {
 public:
  /**
   * \brief Creates a string.
   *
   * \param str the string that will be claimed, can be null.
   */
  explicit sdl_string(Owner<char*> str) noexcept : mStr{str} {}

  /**
   * \brief Returns the internal string, which might be null.
   *
   * \return the internal string; `nullptr` if there is none.
   */
  [[nodiscard]] auto get() const noexcept -> const char* { return mStr.get(); }

  /**
   * \brief Returns a copy of the internal string.
   *
   * \details This function returns the empty string if the internal string is a null
   * pointer.
   *
   * \return a copy of the internal string.
   */
  [[nodiscard]] auto copy() const -> std::string
  {
    if (mStr) {
      return std::string{get()};
    }
    else {
      return std::string{};
    }
  }

  /**
   * \brief Indicates whether or not the internal string is non-null.
   *
   * \return `true` if the internal string is non-null; `false` otherwise.
   */
  explicit operator bool() const noexcept { return mStr.operator bool(); }

 private:
  std::unique_ptr<char, detail::SDLDeleter> mStr;
};

}  // namespace cen

#endif  // CENTURION_SDL_STRING_HPP_
