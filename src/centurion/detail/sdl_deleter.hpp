#ifndef CENTURION_DETAIL_SDL_DELETER_HPP_
#define CENTURION_DETAIL_SDL_DELETER_HPP_

#include <SDL.h>

/// \cond FALSE

namespace cen::detail {

struct sdl_deleter final
{
  void operator()(void* ptr) noexcept { SDL_free(ptr); }
};

}  // namespace cen::detail

/// \endcond

#endif  // CENTURION_DETAIL_SDL_DELETER_HPP_
