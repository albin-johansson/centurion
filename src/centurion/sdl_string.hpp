#ifndef CENTURION_SDL_STRING_HEADER
#define CENTURION_SDL_STRING_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr
#include <string>  // string

#include "../misc/czstring.hpp"
#include "../misc/owner.hpp"
#include "centurion_cfg.hpp"
#include "detail/sdl_deleter.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \class sdl_string
 *
 * \brief Represents a string obtained from SDL, usually a `char*` that has to
 * be freed using `SDL_free`.
 *
 * \since 5.0.0
 *
 * \headerfile sdl_string.hpp
 */
class sdl_string final
{
 public:
  /**
   * \brief
   *
   * \param str the string that will be claimed, can be null.
   *
   * \since 5.0.0
   */
  explicit sdl_string(owner<zstring> str) noexcept : m_str{str}
  {}

  /**
   * \brief Returns the internal string, which might be null.
   *
   * \return the internal string; `nullptr` if there is none.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get() const noexcept -> czstring
  {
    return m_str.get();
  }

  /**
   * \brief Returns a copy of the internal string.
   *
   * \details This function returns the empty string if the internal string
   * is a null pointer.
   *
   * \return a copy of the internal string.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto copy() const -> std::string
  {
    if (m_str)
    {
      return std::string{get()};
    }
    else
    {
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

}  // namespace cen

#endif  // CENTURION_SDL_STRING_HEADER
