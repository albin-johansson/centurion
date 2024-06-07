// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/core/version.hpp"

namespace cen::inline v8_0_0 {

auto operator<<(std::ostream& stream, const version& ver) -> std::ostream&
{
  stream << ver.major << '.' << ver.minor << '.' << ver.patch;
  return stream;
}

auto sdl_linked_version() noexcept -> version
{
  const auto version = SDL_GetVersion();
  return {
    SDL_VERSIONNUM_MAJOR(version),
    SDL_VERSIONNUM_MINOR(version),
    SDL_VERSIONNUM_MICRO(version),
  };
}

#ifndef CENTURION_NO_SDL_IMAGE

auto img_linked_version() noexcept -> version
{
  const auto version = IMG_Version();
  return {
    SDL_VERSIONNUM_MAJOR(version),
    SDL_VERSIONNUM_MINOR(version),
    SDL_VERSIONNUM_MICRO(version),
  };
}

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

auto mix_linked_version() noexcept -> version
{
  const auto version = Mix_Version();
  return {
    SDL_VERSIONNUM_MAJOR(version),
    SDL_VERSIONNUM_MINOR(version),
    SDL_VERSIONNUM_MICRO(version),
  };
}

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

auto ttf_linked_version() noexcept -> version
{
  const auto version = TTF_Version();
  return {
    SDL_VERSIONNUM_MAJOR(version),
    SDL_VERSIONNUM_MINOR(version),
    SDL_VERSIONNUM_MICRO(version),
  };
}

#endif  // CENTURION_NO_SDL_TTF

}  // namespace cen::inline v8_0_0
