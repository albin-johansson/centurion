#ifndef CENTURION_JOYSTICK_HINTS_HEADER
#define CENTURION_JOYSTICK_HINTS_HEADER

#include <SDL.h>

#include "../centurion_cfg.hpp"
#include "../detail/hints_impl.hpp"
#include "../misc/czstring.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \addtogroup configuration
/// \{

namespace cen::hint::joystick {

struct allow_background_events final
    : detail::bool_hint<allow_background_events>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS;
  }
};

struct use_hidapi final : detail::bool_hint<use_hidapi>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_HIDAPI;
  }
};

struct use_hidapi_ps4 final : detail::bool_hint<use_hidapi_ps4>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_HIDAPI_PS4;
  }
};

struct use_hidapi_ps4_rumble final : detail::bool_hint<use_hidapi_ps4_rumble>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE;
  }
};

struct use_hidapi_steam final : detail::bool_hint<use_hidapi_steam>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_HIDAPI_STEAM;
  }
};

struct use_hidapi_switch final : detail::bool_hint<use_hidapi_switch>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_HIDAPI_SWITCH;
  }
};

struct use_hidapi_xbox final : detail::bool_hint<use_hidapi_xbox>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_HIDAPI_XBOX;
  }
};

#if SDL_VERSION_ATLEAST(2, 0, 12)

struct use_hidapi_game_cube final : detail::bool_hint<use_hidapi_game_cube>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_HIDAPI_GAMECUBE;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)

struct use_hidapi_ps5 final : detail::bool_hint<use_hidapi_ps5>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_HIDAPI_PS5;
  }
};

struct use_raw_input final : detail::bool_hint<use_raw_input>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_RAWINPUT;
  }
};

struct hidapi_correlate_xinput final
    : detail::bool_hint<hidapi_correlate_xinput>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_JOYSTICK_HIDAPI_CORRELATE_XINPUT;
  }
};

struct linux_use_deadzones final : detail::bool_hint<linux_use_deadzones>
{
  [[nodiscard]] constexpr static auto name() noexcept -> czstring
  {
    return SDL_HINT_LINUX_JOYSTICK_DEADZONES;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen::hint::joystick

/// \} End of group configuration

#endif  // CENTURION_JOYSTICK_HINTS_HEADER