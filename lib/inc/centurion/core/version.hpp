// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

#include <ostream>

#include <SDL3/SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL3_image/SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL3_mixer/SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL3_ttf/SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

#define CENTURION_VERSION_MAJOR 8
#define CENTURION_VERSION_MINOR 0
#define CENTURION_VERSION_PATCH 0

#define CENTURION_MAKE_VERSION_NUMBER(X, Y, Z) \
  (((X) * 1'000) + ((Y) * 100) + (Z))

#define CENTURION_VERSION_NUMBER                         \
  CENTURION_MAKE_VERSION_NUMBER(CENTURION_VERSION_MAJOR, \
                                CENTURION_VERSION_MINOR, \
                                CENTURION_VERSION_PATCH)

#define CENTURION_VERSION_AT_LEAST(X, Y, Z) \
  CENTURION_VERSION_NUMBER >= CENTURION_MAKE_VERSION_NUMBER(X, Y, Z)

#define CENTURION_SDL_VERSION_IS(X, Y, Z)                      \
  ((SDL_MAJOR_VERSION == (X)) && (SDL_MINOR_VERSION == (Y)) && \
   (SDL_MICRO_VERSION == (Z)))

namespace cen::inline v8_0_0 {

struct version final
{
  int major;
  int minor;
  int patch;

  [[nodiscard]]
  constexpr static auto current() noexcept -> version
  {
    return {CENTURION_VERSION_MAJOR,
            CENTURION_VERSION_MINOR,
            CENTURION_VERSION_PATCH};
  }

  [[nodiscard]]
  constexpr static auto at_least(const int major,
                                 const int minor,
                                 const int patch) noexcept -> bool
  {
    return CENTURION_VERSION_AT_LEAST(major, minor, patch);
  }
};

auto operator<<(std::ostream& stream, const version& ver) -> std::ostream&;

[[nodiscard]]
constexpr auto sdl_header_version() noexcept -> version
{
  return {SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION};
}

// SDL_GetVersion
[[nodiscard]]
auto sdl_linked_version() noexcept -> version;

#ifndef CENTURION_NO_SDL_IMAGE

[[nodiscard]]
constexpr auto img_header_version() noexcept -> version
{
  return {SDL_IMAGE_MAJOR_VERSION,
          SDL_IMAGE_MINOR_VERSION,
          SDL_IMAGE_MICRO_VERSION};
}

// IMG_Version
[[nodiscard]]
auto img_linked_version() noexcept -> version;

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

[[nodiscard]]
constexpr auto mix_header_version() noexcept -> version
{
  return {SDL_MIXER_MAJOR_VERSION,
          SDL_MIXER_MINOR_VERSION,
          SDL_MIXER_MICRO_VERSION};
}

// Mix_Version
[[nodiscard]]
auto mix_linked_version() noexcept -> version;

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

[[nodiscard]]
constexpr auto ttf_header_version() noexcept -> version
{
  return {SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_MICRO_VERSION};
}

// TTF_Version
[[nodiscard]]
auto ttf_linked_version() noexcept -> version;

#endif  // CENTURION_NO_SDL_TTF

}  // namespace cen::inline v8_0_0
