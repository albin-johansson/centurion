#ifndef CENTURION_D3D_HINTS_HEADER
#define CENTURION_D3D_HINTS_HEADER

#include <SDL.h>

#include "../core/str.hpp"
#include "../detail/hints_impl.hpp"

namespace cen::hint::d3d {

/// \addtogroup hints
/// \{

struct v11_debug final : detail::bool_hint<v11_debug>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_RENDER_DIRECT3D11_DEBUG;
  }
};

struct thread_safe final : detail::bool_hint<thread_safe>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_RENDER_DIRECT3D_THREADSAFE;
  }
};

/// \} End of group hints

}  // namespace cen::hint::d3d

#endif  // CENTURION_D3D_HINTS_HEADER