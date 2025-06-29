// Copyright (C) 2025 Albin Johansson

#include "centurion/init.hpp"

namespace cen {

SDL::SDL() noexcept :
  mQuit {[]() noexcept { SDL_Quit(); }}
{}

auto SDL::init(const SDL_InitFlags flags) noexcept -> std::optional<SDL>
{
  if (!SDL_Init(flags)) {
    return std::nullopt;
  }

  return SDL {};
}

}  // namespace cen
