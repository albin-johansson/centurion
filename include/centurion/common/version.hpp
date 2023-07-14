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

#ifndef CENTURION_COMMON_VERSION_HPP_
#define CENTURION_COMMON_VERSION_HPP_

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

#include <centurion/common/primitives.hpp>

#define CEN_VERSION_MAJOR 8U
#define CEN_VERSION_MINOR 0U
#define CEN_VERSION_PATCH 0U

#define CEN_VERSION_NUMBER \
  SDL_VERSIONNUM(CEN_VERSION_MAJOR, CEN_VERSION_MINOR, CEN_VERSION_PATCH)

#define CEN_VERSION_AT_LEAST(X, Y, Z) CEN_VERSION_NUMBER >= SDL_VERSIONNUM(X, Y, Z)

namespace cen {

// TODO comparison operators?
struct Version final {
  uint8 major {};
  uint8 minor {};
  uint8 patch {};

  [[nodiscard]] constexpr auto as_number() const noexcept -> uint32
  {
    return static_cast<uint32>(SDL_VERSIONNUM(major, minor, patch));
  }

  [[nodiscard]] constexpr static auto of_centurion() noexcept -> Version
  {
    return {
        CEN_VERSION_MAJOR,
        CEN_VERSION_MINOR,
        CEN_VERSION_PATCH,
    };
  }

  [[nodiscard]] constexpr static auto of_compiled_sdl() noexcept -> Version
  {
    return {
        SDL_MAJOR_VERSION,
        SDL_MINOR_VERSION,
        SDL_PATCHLEVEL,
    };
  }

  [[nodiscard]] static auto of_linked_sdl() noexcept -> Version
  {
    SDL_version version = {};
    SDL_GetVersion(&version);
    return {version.major, version.minor, version.patch};
  }

#if CEN_USE_SDL_IMAGE

  [[nodiscard]] constexpr static auto of_compiled_sdl_image() noexcept -> Version
  {
    return {
        SDL_IMAGE_MAJOR_VERSION,
        SDL_IMAGE_MINOR_VERSION,
        SDL_IMAGE_PATCHLEVEL,
    };
  }

  [[nodiscard]] static auto of_linked_sdl_image() noexcept -> Version
  {
    const auto* version = IMG_Linked_Version();
    return {version->major, version->minor, version->patch};
  }

#endif  // CEN_USE_SDL_IMAGE

#if CEN_USE_SDL_MIXER

  [[nodiscard]] constexpr static auto of_compiled_sdl_mixer() noexcept -> Version
  {
    return {
        SDL_MIXER_MAJOR_VERSION,
        SDL_MIXER_MINOR_VERSION,
        SDL_MIXER_PATCHLEVEL,
    };
  }

  [[nodiscard]] static auto of_linked_sdl_mixer() noexcept -> Version
  {
    const auto* version = Mix_Linked_Version();
    return {version->major, version->minor, version->patch};
  }

#endif  // CEN_USE_SDL_MIXER

#if CEN_USE_SDL_TTF

  [[nodiscard]] constexpr static auto of_compiled_sdl_ttf() noexcept -> Version
  {
    return {
        TTF_MAJOR_VERSION,
        TTF_MINOR_VERSION,
        TTF_PATCHLEVEL,
    };
  }

  [[nodiscard]] static auto of_linked_sdl_ttf() noexcept -> Version
  {
    const auto* version = TTF_Linked_Version();
    return {version->major, version->minor, version->patch};
  }

#endif  // CEN_USE_SDL_TTF
};

}  // namespace cen

#endif  // CENTURION_COMMON_VERSION_HPP_
