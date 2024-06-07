// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/core/memory.hpp"

namespace cen::inline v8_0_0 {

void sdl_free_deleter::operator()(void* ptr) const noexcept
{
  SDL_free(ptr);
}

}  // namespace cen::inline v8_0_0
