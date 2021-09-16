#ifndef CENTURION_SDL_STRING_HEADER
#define CENTURION_SDL_STRING_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr
#include <string>  // string

#include "../detail/sdl_deleter.hpp"
#include "owner.hpp"
#include "str.hpp"

namespace cen {

/// \addtogroup core
/// \{

/**
 * \class sdl_string
 *
 * \brief Represents an SDL string.
 *
 * \details Certain SDL APIs return `char*` strings that need to be freed using
 * `SDL_free`, this class serves as a small wrapper around such strings. Use the `copy()`
 * member function to convert the string into a corresponding `std::string`.
 *
 * \note Instances of `sdl_string` might manage null strings. Use the overloaded `operator
 * bool()` in order to determine whether or not any associated string is null.
 *
 * \since 5.0.0
 */
class sdl_string final
{
 public:
  /**
   * \brief Creates a string.
   *
   * \param str the string that will be claimed, can be null.
   *
   * \since 5.0.0
   */
  explicit sdl_string(owner<char*> str) noexcept : m_str{str}
  {}

  /**
   * \brief Returns the internal string, which might be null.
   *
   * \return the internal string; `nullptr` if there is none.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get() const noexcept -> str
  {
    return m_str.get();
  }

  /**
   * \brief Returns a copy of the internal string.
   *
   * \details This function returns the empty string if the internal string is a null
   * pointer.
   *
   * \return a copy of the internal string.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto copy() const -> std::string
  {
    if (m_str) {
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
   *
   * \since 5.0.0
   */
  explicit operator bool() const noexcept
  {
    return m_str.operator bool();
  }

 private:
  std::unique_ptr<char, detail::sdl_deleter<char>> m_str;
};

/// \} End of group core

}  // namespace cen

#endif  // CENTURION_SDL_STRING_HEADER
