/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_IO_PATHS_HPP_
#define CENTURION_IO_PATHS_HPP_

#include <SDL.h>

#include <cassert>  // assert
#include <string>   // string

#include "../common.hpp"

namespace cen {

/// Returns the directory from which the application launched from.
[[nodiscard]] inline auto base_path() -> sdl_string
{
  return sdl_string {SDL_GetBasePath()};
}

/// Returns the preferred path for storing application related files.
[[nodiscard]] inline auto preferred_path(const char* org, const char* app) -> sdl_string
{
  /* Looking at the SDL source code, it actually seems fine to supply a null
     string for the organization name. However, I haven't been able to find any
     documentation providing this guarantee, so we simply disallow null
     organization names. */
  assert(org);
  assert(app);
  return sdl_string {SDL_GetPrefPath(org, app)};
}

[[nodiscard]] inline auto preferred_path(const std::string& org, const std::string& app)
    -> sdl_string
{
  return preferred_path(org.c_str(), app.c_str());
}

}  // namespace cen

#endif  // CENTURION_IO_PATHS_HPP_
