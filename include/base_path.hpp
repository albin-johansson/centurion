/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#ifndef CENTURION_BASE_PATH_HEADER
#define CENTURION_BASE_PATH_HEADER

#include <SDL.h>

#include <ostream>  // ostream
#include <string>   // string

#include "centurion_cfg.hpp"
#include "sdl_string.hpp"

namespace cen {

/**
 * \class base_path
 *
 * \ingroup system
 *
 * \brief A wrapper for the application path obtained through `SDL_GetBasePath`.
 *
 * \details There is no guarantee that the application path is obtainable, so
 * you should always check for null when dealing with a base path instance.
 *
 * \see `SDL_GetBasePath`
 *
 * \since 3.0.0
 *
 * \deprecated Since 5.2.0, use ``get_base_path()`` instead.
 *
 * \headerfile base_path.hpp
 */
class [[deprecated]] base_path final
{
 public:
  /**
   * \brief Obtains the path of the application executable.
   *
   * \note This might be an expensive operation, so it's recommended to create
   * only one instance of this class and cache it.
   *
   * \since 3.0.0
   */
  base_path() : m_path{SDL_GetBasePath()}
  {}

  /**
   * \brief Indicates whether or not there is a non-null string in the base path
   * instance.
   *
   * \return `true` if the internal string is non-null; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return m_path.operator bool();
  }

  /**
   * \brief Returns the path of the application executable.
   *
   * \note The returned pointer might be null! You should always check the
   * returned pointer.
   *
   * \return the path of the application executable, might be `nullptr`.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto get() const noexcept -> czstring
  {
    return m_path.get();
  }

 private:
  sdl_string m_path;
};

/**
 * \brief Returns the "base" path associated with the application.
 *
 * \details The returned string represents the path to the directory from which
 * application was run from, and will end with a path separator (e.g. "\\" or
 * "/").
 *
 * \note This might be an expensive operation, so it's recommended to only call
 * this function once and cache the returned path.
 *
 * \return the base path of the application; a null string is returned if the
 * path cannot be obtained.
 *
 * \since 5.2.0
 */
[[nodiscard]] inline auto get_base_path() -> sdl_string
{
  return sdl_string{SDL_GetBasePath()};
}

/**
 * \brief Returns a textual representation of a base path.
 *
 * \ingroup system
 *
 * \param path the base path that will be converted.
 *
 * \return a string that represents a base path.
 *
 * \deprecated Since 5.2.0.
 *
 * \since 5.0.0
 */
[[nodiscard, deprecated]] inline auto to_string(const base_path& path)
    -> std::string
{
  const std::string str = path ? path.get() : "N/A";
  return "[base_path | path: \"" + str + "\"]";
}

/**
 * \brief Prints a textual representation of a base path.
 *
 * \ingroup system
 *
 * \param stream the stream that will be used.
 * \param path the base path that will be printed.
 *
 * \return the used stream.
 *
 * \deprecated Since 5.2.0.
 *
 * \since 5.0.0
 */
[[deprecated]] inline auto operator<<(std::ostream& stream,
                                      const base_path& path) -> std::ostream&
{
  stream << to_string(path);
  return stream;
}

}  // namespace cen

#endif  // CENTURION_BASE_PATH_HEADER
