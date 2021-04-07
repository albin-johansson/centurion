#ifndef CENTURION_D3D_HINTS_HEADER
#define CENTURION_D3D_HINTS_HEADER

#include <SDL.h>

#include "../detail/hints_impl.hpp"
#include "../misc/czstring.hpp"

/// \addtogroup configuration
/// \{

namespace cen::hint::d3d {

struct v11_debug final : detail::bool_hint<v11_debug>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_RENDER_DIRECT3D11_DEBUG;
  }
};

struct thread_safe final : detail::bool_hint<thread_safe>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_RENDER_DIRECT3D_THREADSAFE;
  }
};

}  // namespace cen::hint::d3d

/// \} End of group configuration

#endif  // CENTURION_D3D_HINTS_HEADER