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

#include <SDL3/SDL.h>

#if CEN_USE_SDL_IMAGE
#include <SDL3/SDL_image.h>
#endif  // CEN_USE_SDL_IMAGE

#if CEN_USE_SDL_MIXER
#include <SDL3/SDL_mixer.h>
#endif  // CEN_USE_SDL_MIXER

#if CEN_USE_SDL_TTF
#include <SDL3/SDL_ttf.h>
#endif  // CEN_USE_SDL_TTF

#include <array>      // array
#include <cstring>    // strncpy, strncpy_s
#include <exception>  // exception

namespace cen {

class Error : public std::exception {
 public:
  explicit Error(const char* what = nullptr) noexcept
  {
#ifdef _MSC_VER
    strncpy_s(mWhat.data(), mWhat.size(), what ? what : "?", _TRUNCATE);
#else
    std::strncpy(mWhat.data(), what ? what : "?", mWhat.size() - 1);
#endif  // _MSC_VER
  }

  [[nodiscard]] auto what() const noexcept -> const char* override { return mWhat.data(); }

 private:
  // We use an array here instead of a string to avoid a dynamic allocation.
  std::array<char, 128> mWhat {};
};

class SDLError final : public Error {
 public:
  using Error::Error;

  SDLError() noexcept : SDLError {SDL_GetError()} {}
};

#if CEN_USE_SDL_IMAGE

class SDLImageError final : public Error {
 public:
  using Error::Error;

  SDLImageError() noexcept : SDLImageError {IMG_GetError()} {}
};

#endif  // CEN_USE_SDL_IMAGE

#if CEN_USE_SDL_MIXER

class SDLMixerError final : public Error {
 public:
  using Error::Error;

  SDLMixerError() noexcept : SDLMixerError {Mix_GetError()} {}
};

#endif  // CEN_USE_SDL_MIXER

#if CEN_USE_SDL_TTF

class SDLTTFError final : public Error {
 public:
  using Error::Error;

  SDLTTFError() noexcept : SDLTTFError {TTF_GetError()} {}
};

#endif  // CEN_USE_SDL_TTF

}  // namespace cen

#endif  // CENTURION_COMMON_ERRORS_HPP_
