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

#ifndef CENTURION_VERSION_HPP_
#define CENTURION_VERSION_HPP_

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

#include <cassert>  // assert

#define CENTURION_VERSION_MAJOR 7
#define CENTURION_VERSION_MINOR 3
#define CENTURION_VERSION_PATCH 0

#define CENTURION_MAKE_VERSION_NUMBER(X, Y, Z) (((X)*1'000) + ((Y)*100) + (Z))

#define CENTURION_VERSION_NUMBER                         \
  CENTURION_MAKE_VERSION_NUMBER(CENTURION_VERSION_MAJOR, \
                                CENTURION_VERSION_MINOR, \
                                CENTURION_VERSION_PATCH)

#define CENTURION_VERSION_AT_LEAST(X, Y, Z) \
  CENTURION_VERSION_NUMBER >= CENTURION_MAKE_VERSION_NUMBER(X, Y, Z)

#define CENTURION_SDL_VERSION_IS(X, Y, Z) \
  ((SDL_MAJOR_VERSION == (X)) && (SDL_MINOR_VERSION == (Y)) && (SDL_PATCHLEVEL == (Z)))

namespace cen {

struct version final
{
  int major{};
  int minor{};
  int patch{};
};

/// Returns the current Centurion version.
[[nodiscard]] constexpr auto current_version() noexcept -> version
{
  return {CENTURION_VERSION_MAJOR, CENTURION_VERSION_MINOR, CENTURION_VERSION_PATCH};
}

/// Indicates whether the current Centurion version is at least the specific version.
[[nodiscard]] constexpr auto version_at_least(const int major,
                                              const int minor,
                                              const int patch) noexcept -> bool
{
  return CENTURION_VERSION_AT_LEAST(major, minor, patch);
}

/// Returns the compile-time version of SDL2.
[[nodiscard]] constexpr auto sdl_version() noexcept -> SDL_version
{
  return {SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL};
}

/// Returns the version of SDL2 that the program was linked against.
[[nodiscard]] inline auto sdl_linked_version() noexcept -> SDL_version
{
  SDL_version version{};
  SDL_GetVersion(&version);
  return version;
}

#ifndef CENTURION_NO_SDL_IMAGE

/// Returns the compile-time version of SDL2_image.
[[nodiscard]] constexpr auto sdl_image_version() noexcept -> SDL_version
{
  return {SDL_IMAGE_MAJOR_VERSION, SDL_IMAGE_MINOR_VERSION, SDL_IMAGE_PATCHLEVEL};
}

/// Returns the version of SDL2_image that the program was linked against.
[[nodiscard]] inline auto sdl_image_linked_version() noexcept -> SDL_version
{
  const auto* version = IMG_Linked_Version();
  assert(version);
  return *version;
}

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

/// Returns the compile-time version of SDL2_mixer.
[[nodiscard]] constexpr auto sdl_mixer_version() noexcept -> SDL_version
{
  return {SDL_MIXER_MAJOR_VERSION, SDL_MIXER_MINOR_VERSION, SDL_MIXER_PATCHLEVEL};
}

/// Returns the version of SDL2_mixer that the program was linked against.
[[nodiscard]] inline auto sdl_mixer_linked_version() noexcept -> SDL_version
{
  const auto* version = Mix_Linked_Version();
  assert(version);
  return *version;
}

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

/// Returns the compile-time version of SDL2_ttf.
[[nodiscard]] constexpr auto sdl_ttf_version() noexcept -> SDL_version
{
  return {SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_PATCHLEVEL};
}

/// Returns the version of SDL2_ttf that the program was linked against.
[[nodiscard]] inline auto sdl_ttf_linked_version() noexcept -> SDL_version
{
  const auto* version = TTF_Linked_Version();
  assert(version);
  return *version;
}

#endif  // CENTURION_NO_SDL_TTF

}  // namespace cen

#endif  // CENTURION_VERSION_HPP_
