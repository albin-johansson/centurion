#ifndef CENTURION_XINPUT_HINTS_HEADER
#define CENTURION_XINPUT_HINTS_HEADER

#include <SDL.h>

#include "../core/common.hpp"
#include "../detail/hints_impl.hpp"

namespace cen::hint::xinput {

/// \addtogroup hints
/// \{

struct is_enabled final : detail::bool_hint<is_enabled>
{
  [[nodiscard]] constexpr static auto name() noexcept -> cstr
  {
    return SDL_HINT_XINPUT_ENABLED;
  }
};

struct use_old_joystick_mapping final : detail::bool_hint<use_old_joystick_mapping>
{
  [[nodiscard]] constexpr static auto name() noexcept -> cstr
  {
    return SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING;
  }
};

/// \} End of group hints

}  // namespace cen::hint::xinput

#endif  // CENTURION_XINPUT_HINTS_HEADER