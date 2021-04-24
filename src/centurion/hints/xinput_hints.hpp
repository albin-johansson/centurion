#ifndef CENTURION_XINPUT_HINTS_HEADER
#define CENTURION_XINPUT_HINTS_HEADER

#include <SDL.h>

#include "../core/czstring.hpp"
#include "../detail/hints_impl.hpp"

/// \addtogroup configuration
/// \{

namespace cen::hint::xinput {

struct is_enabled final : detail::bool_hint<is_enabled>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_XINPUT_ENABLED;
  }
};

struct use_old_joystick_mapping final : detail::bool_hint<use_old_joystick_mapping>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING;
  }
};

}  // namespace cen::hint::xinput

/// \} End of group configuration

#endif  // CENTURION_XINPUT_HINTS_HEADER