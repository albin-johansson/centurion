#ifndef CENTURION_CORE_MEMORY_HPP_
#define CENTURION_CORE_MEMORY_HPP_

#include <SDL.h>

#include <memory>  // unique_ptr

namespace cen {

template <typename T>
struct Deleter;

template <>
struct Deleter<SDL_RWops> final
{
  void operator()(SDL_RWops* ops) noexcept
  {
    SDL_RWclose(ops);
  }
};

template <typename T>
using Managed = std::unique_ptr<T, Deleter<T>>;

}  // namespace cen

#endif  // CENTURION_CORE_MEMORY_HPP_
