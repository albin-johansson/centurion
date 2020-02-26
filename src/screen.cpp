#ifndef CENTURION_SCREEN_SOURCE
#define CENTURION_SCREEN_SOURCE

#include <SDL.h>

#include "screen.h"

namespace centurion {
namespace system {

CENTURION_DEF
void Screen::set_screen_saver_enabled(bool enabled) noexcept
{
  if (enabled) {
    SDL_EnableScreenSaver();
  } else {
    SDL_DisableScreenSaver();
  }
}

CENTURION_DEF
bool Screen::is_screen_saver_enabled() noexcept
{
  return SDL_IsScreenSaverEnabled();
}

CENTURION_DEF
int Screen::get_width() noexcept
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.w;
}

CENTURION_DEF
int Screen::get_height() noexcept
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.h;
}

CENTURION_DEF
int Screen::get_refresh_rate() noexcept
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.refresh_rate;
}

CENTURION_DEF
video::PixelFormat Screen::get_pixel_format() noexcept
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return static_cast<video::PixelFormat>(mode.format);
}

}  // namespace system
}  // namespace centurion

#endif  // CENTURION_SCREEN_SOURCE