// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#pragma once

#include <memory>

#include <SDL3/SDL.h>

namespace cen::inline v8_0_0 {

struct sdl_free_deleter
{
  // SDL_free
  void operator()(void* ptr) const noexcept;
};

template <typename T>
using unique_sdl_ptr = std::unique_ptr<T, sdl_free_deleter>;

}  // namespace cen::inline v8_0_0
