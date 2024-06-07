// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

#include <optional>

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

#include "centurion/detail/scope_exit.hpp"

namespace cen::inline v8_0_0 {

class sdl_library final
{
 public:
  // SDL_Init
  [[nodiscard]]
  static auto init(SDL_InitFlags flags) noexcept -> std::optional<sdl_library>;

 private:
  detail::scope_exit_fn m_dispose [[maybe_unused]];

  [[nodiscard]]
  sdl_library() noexcept;
};

#ifndef CENTURION_NO_SDL_IMAGE

class img_library final
{
 public:
  // IMG_Init
  [[nodiscard]]
  static auto init(int flags) noexcept -> std::optional<img_library>;

 private:
  detail::scope_exit_fn m_dispose [[maybe_unused]];

  [[nodiscard]]
  img_library() noexcept;
};

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

class mix_library final
{
 public:
  // TTF_Init
  [[nodiscard]]
  static auto init(MIX_InitFlags flags) noexcept -> std::optional<mix_library>;

 private:
  detail::scope_exit_fn m_dispose [[maybe_unused]];

  [[nodiscard]]
  mix_library() noexcept;
};

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

class ttf_library final
{
 public:
  // TTF_Init
  [[nodiscard]]
  static auto init() noexcept -> std::optional<ttf_library>;

 private:
  detail::scope_exit_fn m_dispose [[maybe_unused]];

  [[nodiscard]]
  ttf_library() noexcept;
};

#endif  // CENTURION_NO_SDL_TTF

}  // namespace cen::inline v8_0_0
