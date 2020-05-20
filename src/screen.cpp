#ifndef CENTURION_SCREEN_SOURCE
#define CENTURION_SCREEN_SOURCE

#include "screen.h"

#include <SDL.h>

namespace centurion {

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
bool Screen::screen_saver_enabled() noexcept
{
  return SDL_IsScreenSaverEnabled();
}

CENTURION_DEF
int Screen::width() noexcept
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.w;
}

CENTURION_DEF
int Screen::height() noexcept
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.h;
}

CENTURION_DEF
Area Screen::size() noexcept
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return {mode.w, mode.h};
}

CENTURION_DEF
int Screen::refresh_rate() noexcept
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.refresh_rate;
}

CENTURION_DEF
PixelFormat Screen::pixel_format() noexcept
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return static_cast<PixelFormat>(mode.format);
}

}  // namespace centurion

#endif  // CENTURION_SCREEN_SOURCE