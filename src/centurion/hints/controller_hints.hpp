#ifndef CENTURION_CONTROLLER_HINTS_HEADER
#define CENTURION_CONTROLLER_HINTS_HEADER

#include <SDL.h>

#include "../centurion_cfg.hpp"
#include "../detail/hints_impl.hpp"
#include "../misc/czstring.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \addtogroup configuration
/// \{

// TODO Centurion 6: Rename this namespace to controller for API consistency
namespace cen::hint::gamecontroller {

#if SDL_VERSION_ATLEAST(2, 0, 12)

struct use_button_labels final : detail::bool_hint<use_button_labels>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS;
  }
};

struct type final : detail::string_hint<type>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_GAMECONTROLLERTYPE;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

struct config final : detail::string_hint<config>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_GAMECONTROLLERCONFIG;
  }
};

struct config_file final : detail::string_hint<config_file>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_GAMECONTROLLERCONFIG_FILE;
  }
};

struct ignore_devices final : detail::string_hint<ignore_devices>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES;
  }
};

struct ignore_devices_except final : detail::string_hint<ignore_devices_except>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES_EXCEPT;
  }
};

}  // namespace cen::hint::gamecontroller

/// \} End of group configuration

#endif  // CENTURION_CONTROLLER_HINTS_HEADER