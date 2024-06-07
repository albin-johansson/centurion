// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/core/init.hpp"

#include "centurion/core/error.hpp"

namespace cen::inline v8_0_0 {

sdl_library::sdl_library() noexcept
  : m_dispose {[]() noexcept { SDL_Quit(); }}
{}

auto sdl_library::init(const SDL_InitFlags flags) noexcept
    -> std::optional<sdl_library>
{
  const auto result = SDL_Init(flags);

  if (result != 0) {
    emit_sdl_error();
    return std::nullopt;
  }

  return sdl_library {};
}

#ifndef CENTURION_NO_SDL_IMAGE

img_library::img_library() noexcept
  : m_dispose {[]() noexcept { IMG_Quit(); }}
{}

auto img_library::init(const int flags) noexcept -> std::optional<img_library>
{
  const auto real_flags = IMG_Init(flags);

  if (real_flags != flags) {
    emit_img_error();
    return std::nullopt;
  }

  return img_library {};
}

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

mix_library::mix_library() noexcept
  : m_dispose {[]() noexcept { Mix_Quit(); }}
{}

auto mix_library::init(const MIX_InitFlags flags) noexcept
    -> std::optional<mix_library>
{
  const auto real_flags = Mix_Init(flags);

  if (real_flags != flags) {
    emit_mix_error();
    return std::nullopt;
  }

  return mix_library {};
}

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

ttf_library::ttf_library() noexcept
  : m_dispose {[]() noexcept { TTF_Quit(); }}
{}

auto ttf_library::init() noexcept -> std::optional<ttf_library>
{
  const auto ec = TTF_Init();

  if (ec != 0) {
    emit_ttf_error();
    return std::nullopt;
  }

  return ttf_library {};
}

#endif  // CENTURION_NO_SDL_TTF

}  // namespace cen::inline v8_0_0
