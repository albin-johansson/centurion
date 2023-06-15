/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#ifndef CENTURION_COMMON_ERRORS_HPP_
#define CENTURION_COMMON_ERRORS_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

#include <array>      // array
#include <cstring>    // strncpy, strncpy_s
#include <exception>  // exception

namespace cen {

/// The base class of all exceptions explicitly thrown by the library.
class exception : public std::exception {
 public:
  explicit exception(const char* what = nullptr) noexcept
  {
#ifdef _MSC_VER
    strncpy_s(mWhat.data(), mWhat.size(), what ? what : "?", _TRUNCATE);
#else
    std::strncpy(mWhat.data(), what ? what : "?", mWhat.size() - 1);
#endif  // _MSC_VER
  }

  [[nodiscard]] auto what() const noexcept -> const char* override { return mWhat.data(); }

 private:
  // We use an array here instead of a string to avoid a dynamic allocation
  std::array<char, 128> mWhat {};
};

class sdl_error final : public exception {
 public:
  sdl_error() noexcept : exception {SDL_GetError()} {}

  explicit sdl_error(const char* what) noexcept : exception {what} {}
};

#ifndef CENTURION_NO_SDL_IMAGE

class img_error final : public exception {
 public:
  img_error() noexcept : exception {IMG_GetError()} {}

  explicit img_error(const char* what) noexcept : exception {what} {}
};

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_TTF

class ttf_error final : public exception {
 public:
  ttf_error() noexcept : exception {TTF_GetError()} {}

  explicit ttf_error(const char* what) noexcept : exception {what} {}
};

#endif  // CENTURION_NO_SDL_TTF

#ifndef CENTURION_NO_SDL_MIXER

class mix_error final : public exception {
 public:
  mix_error() noexcept : exception {Mix_GetError()} {}

  explicit mix_error(const char* what) noexcept : exception {what} {}
};

#endif  // CENTURION_NO_SDL_MIXER

}  // namespace cen

#endif  // CENTURION_COMMON_ERRORS_HPP_
