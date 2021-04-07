#ifndef CENTURION_DETAIL_SDL_DELETER_HEADER
#define CENTURION_DETAIL_SDL_DELETER_HEADER

#include <SDL.h>

/// \cond FALSE
namespace cen::detail {

template <typename T>
struct sdl_deleter final
{
  void operator()(T* ptr) noexcept
  {
    SDL_free(ptr);
  }
};

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_SDL_DELETER_HEADER
