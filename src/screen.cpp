#ifndef CENTURION_SCREEN_SOURCE
#define CENTURION_SCREEN_SOURCE

#include "screen.hpp"

#include <SDL.h>

namespace centurion::screen {

CENTURION_DEF
void set_screen_saver_enabled(bool enabled) noexcept
{
  if (enabled) {
    SDL_EnableScreenSaver();
  } else {
    SDL_DisableScreenSaver();
  }
}

CENTURION_DEF
auto screen_saver_enabled() noexcept -> bool
{
  return SDL_IsScreenSaverEnabled();
}

CENTURION_DEF
auto width() noexcept -> int
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.w;
}

CENTURION_DEF
auto height() noexcept -> int
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.h;
}

CENTURION_DEF
auto size() noexcept -> area_i
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return {mode.w, mode.h};
}

CENTURION_DEF
auto refresh_rate() noexcept -> int
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.refresh_rate;
}

CENTURION_DEF
auto get_pixel_format() noexcept -> pixel_format
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return static_cast<pixel_format>(mode.format);
}

}  // namespace centurion::screen

#endif  // CENTURION_SCREEN_SOURCE