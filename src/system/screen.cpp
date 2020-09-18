#include "screen.hpp"

#include <SDL.h>

namespace cen::screen {

void set_screen_saver_enabled(bool enabled) noexcept
{
  if (enabled) {
    SDL_EnableScreenSaver();
  } else {
    SDL_DisableScreenSaver();
  }
}

auto screen_saver_enabled() noexcept -> bool
{
  return SDL_IsScreenSaverEnabled();
}

auto width() noexcept -> int
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.w;
}

auto height() noexcept -> int
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.h;
}

auto size() noexcept -> iarea
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return {mode.w, mode.h};
}

auto refresh_rate() noexcept -> int
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return mode.refresh_rate;
}

auto get_pixel_format() noexcept -> pixel_format
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  return static_cast<pixel_format>(mode.format);
}

}  // namespace cen::screen
