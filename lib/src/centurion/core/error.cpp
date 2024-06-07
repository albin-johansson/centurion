// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/core/error.hpp"

#include <cstdio>

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

namespace cen::inline v8_0_0 {
inline namespace error_detail {

inline constexpr error_message_fn _default_error_callback =
    [](const std::string_view msg) noexcept {
      std::fprintf(stderr,
                   "ERROR: %.*s\n",
                   static_cast<int>(msg.size()),
                   msg.data());
    };

inline error_message_fn _error_message_callback = _default_error_callback;

}  // namespace error_detail

void reset_error_message_callback() noexcept
{
  _error_message_callback = _default_error_callback;
}

void set_error_message_callback(const error_message_fn callback) noexcept
{
  _error_message_callback = callback;
}

void emit_error_message(const std::string_view error_message) noexcept
{
  if (_error_message_callback != nullptr) {
    _error_message_callback(error_message);
  }
}

void emit_sdl_error() noexcept
{
  emit_error_message(SDL_GetError());
}

#ifndef CENTURION_NO_SDL_IMAGE

void emit_img_error() noexcept
{
  emit_error_message(IMG_GetError());
}

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

void emit_mix_error() noexcept
{
  emit_error_message(Mix_GetError());
}

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

void emit_ttf_error() noexcept
{
  emit_error_message(TTF_GetError());
}

#endif  // CENTURION_NO_SDL_TTF

}  // namespace cen::inline v8_0_0
