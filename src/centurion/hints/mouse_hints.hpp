#ifndef CENTURION_MOUSE_HINTS_HEADER
#define CENTURION_MOUSE_HINTS_HEADER

#include <SDL.h>

#include "../detail/hints_impl.hpp"
#include "../misc/czstring.hpp"

/// \addtogroup configuration
/// \{

namespace cen::hint::mouse {

struct focus_clickthrough final : detail::bool_hint<focus_clickthrough>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH;
  }
};

struct relative_mode_warp final : detail::bool_hint<relative_mode_warp>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_MOUSE_RELATIVE_MODE_WARP;
  }
};

struct double_click_time final : detail::int_hint<double_click_time>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_MOUSE_DOUBLE_CLICK_TIME;
  }
};

struct double_click_radius final : detail::int_hint<double_click_radius>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_MOUSE_DOUBLE_CLICK_RADIUS;
  }
};

struct normal_speed_scale final : detail::float_hint<normal_speed_scale>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_MOUSE_NORMAL_SPEED_SCALE;
  }
};

struct relative_speed_scale final : detail::float_hint<relative_speed_scale>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_MOUSE_RELATIVE_SPEED_SCALE;
  }
};

#if SDL_VERSION_ATLEAST(2, 0, 14)

struct relative_scaling final : detail::bool_hint<relative_scaling>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_MOUSE_RELATIVE_SCALING;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen::hint::mouse

/// \} End of group configuration

#endif  // CENTURION_MOUSE_HINTS_HEADER