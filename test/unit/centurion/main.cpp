// Copyright (C) 2019-2023 Albin Johansson (MIT License)

#include <iomanip>
#include <iostream>

#include <SDL3/SDL.h>
#include <gtest/gtest.h>

#include "centurion/core/init.hpp"
#include "centurion/core/version.hpp"

auto main(int argc, char* argv[]) -> int
{
  std::cout << "Centurion version: " << cen::version::current() << '\n';

  const auto sdl_flags = SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_VIDEO;
  const auto sdl [[maybe_unused]] = cen::sdl_library::init(sdl_flags).value();

  std::cout << "SDL header version: " << cen::sdl_header_version() << '\n';
  std::cout << "SDL linked version: " << cen::sdl_linked_version() << '\n';
  std::cout << "SDL revision: " << std::quoted(SDL_GetRevision()) << '\n';

#ifndef CENTURION_NO_SDL_IMAGE
  const auto img_flags = IMG_INIT_PNG;
  const auto img [[maybe_unused]] = cen::img_library::init(img_flags).value();

  std::cout << "SDL_image header version: " << cen::img_header_version()
            << '\n';
  std::cout << "SDL_image linked version: " << cen::img_linked_version()
            << '\n';
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
  const auto mix_flags = MIX_INIT_MP3;
  const auto mix [[maybe_unused]] = cen::mix_library::init(mix_flags).value();

  std::cout << "SDL_mixer header version: " << cen::mix_header_version()
            << '\n';
  std::cout << "SDL_mixer linked version: " << cen::mix_linked_version()
            << '\n';
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
  const auto ttf [[maybe_unused]] = cen::ttf_library::init().value();

  std::cout << "SDL_ttf header version: " << cen::ttf_header_version() << '\n';
  std::cout << "SDL_ttf linked version: " << cen::ttf_linked_version() << '\n';
#endif  // CENTURION_NO_SDL_TTF

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
