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

#ifndef CENTURION_PREF_PATH_HEADER
#define CENTURION_PREF_PATH_HEADER

#include <SDL.h>

#include <ostream>  // ostream
#include <string>   // string

#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "not_null.hpp"
#include "sdl_string.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup system
/// \{

/**
 * \class pref_path
 *
 * \brief A wrapper for the preferred path for storing application related
 * files.
 *
 * \details This class is used to obtain the "pref dir". Where users are
 * meant to write personal files (such as preferences and save games, etc) that
 * are specific to your application. This directory is unique per user, per
 * application.
 *
 * \since 3.0.0
 *
 * \see `SDL_GetPrefPath`
 *
 * \headerfile pref_path.hpp
 */
class pref_path final
{
 public:
  /**
   * \brief Constructs a `pref_path` instance.
   *
   * \note Only use letters, numbers, and spaces in the supplied strings!
   *
   * \param org the name of your organization, cannot be null.
   * \param app the name of your application, cannot be null.
   *
   * \since 3.0.0
   */
  pref_path(not_null<czstring> org, not_null<czstring> app)
      : m_path{SDL_GetPrefPath(org, app)}
  {}

  /**
   * \brief Indicates whether or not the instance holds a non-null path.
   *
   * \return `true` if the object holds a non-null path; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return m_path.operator bool();
  }

  /**
   * \brief Returns a string that represents the preferred path.
   *
   * \return a string that represents the preferred path.
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
 * \brief Returns a textual representation of a pref path.
 *
 * \param path the pref path that will be converted.
 *
 * \return a string that represents a pref path.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto to_string(const pref_path& path) -> std::string
{
  const std::string str = path ? path.get() : "N/A";
  return "[pref_path | path: \"" + str + "\"]";
}

/**
 * \brief Prints a textual representation of a pref path.
 *
 * \param stream the stream that will be used.
 * \param path the pref path that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
inline auto operator<<(std::ostream& stream, const pref_path& path)
    -> std::ostream&
{
  stream << to_string(path);
  return stream;
}

/// \}

}  // namespace cen

#endif  // CENTURION_PREF_PATH_HEADER