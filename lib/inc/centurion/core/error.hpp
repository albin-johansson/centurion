// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

#include <cstdint>
#include <string_view>

namespace cen::inline v8_0_0 {

enum class result : std::uint8_t
{
  success,
  failure,
};

using error_message_fn = void (*)(std::string_view) noexcept;

void set_error_message_callback(error_message_fn callback) noexcept;

void emit_error_message(std::string_view error_message) noexcept;

void emit_sdl_error() noexcept;

#ifndef CENTURION_NO_SDL_IMAGE

void emit_img_error() noexcept;

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER

void emit_mix_error() noexcept;

#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF

void emit_ttf_error() noexcept;

#endif  // CENTURION_NO_SDL_TTF

}  // namespace cen::inline v8_0_0
