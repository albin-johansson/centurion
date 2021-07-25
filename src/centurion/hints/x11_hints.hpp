#ifndef CENTURION_X11_HINTS_HEADER
#define CENTURION_X11_HINTS_HEADER

#include <SDL.h>

#include "../core/str.hpp"
#include "../detail/hints_impl.hpp"

namespace cen::hint::x11 {

/// \addtogroup hints
/// \{

struct net_wm_ping final : detail::bool_hint<net_wm_ping>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_X11_NET_WM_PING;
  }
};

struct net_wm_bypass_compositor final : detail::bool_hint<net_wm_bypass_compositor>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR;
  }
};

struct xinerama final : detail::bool_hint<xinerama>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_X11_XINERAMA;
  }
};

struct xrandr final : detail::bool_hint<xrandr>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_X11_XRANDR;
  }
};

struct xvidmode final : detail::bool_hint<xvidmode>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_X11_XVIDMODE;
  }
};

#if SDL_VERSION_ATLEAST(2, 0, 12)

struct force_egl final : detail::bool_hint<force_egl>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_X11_FORCE_EGL;
  }
};

struct window_visual_id final : detail::string_hint<window_visual_id>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_X11_WINDOW_VISUALID;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

/// \} End of group hints

}  // namespace cen::hint::x11

#endif  // CENTURION_X11_HINTS_HEADER
