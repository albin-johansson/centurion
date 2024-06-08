// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include <iostream>

#include <SDL3/SDL.h>

#include "centurion/core/init.hpp"

auto main(int, char*[]) -> int
{
  const auto sdl_flags = SDL_INIT_TIMER | SDL_INIT_EVENTS;
  const auto sdl [[maybe_unused]] = cen::sdl_library::init(sdl_flags).value();

#ifndef CENTURION_NO_SDL_IMAGE
  const auto img_flags = IMG_INIT_PNG;
  const auto img [[maybe_unused]] = cen::img_library::init(img_flags).value();
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
  const auto mix_flags = MIX_INIT_MP3;
  const auto mix [[maybe_unused]] = cen::mix_library::init(mix_flags);
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
  const auto ttf [[maybe_unused]] = cen::ttf_library::init().value();
#endif  // CENTURION_NO_SDL_TTF

  std::cout << "Success!\n";
  return 0;
}
