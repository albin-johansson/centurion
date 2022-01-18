#include <gtest/gtest.h>

#include "video.hpp"

namespace {

[[nodiscard]] auto get_sdl_desktop_display_mode(const int index) -> SDL_DisplayMode
{
  SDL_DisplayMode mode{};
  SDL_GetDesktopDisplayMode(index, &mode);
  return mode;
}

[[nodiscard]] auto get_sdl_current_display_mode(const int index) -> SDL_DisplayMode
{
  SDL_DisplayMode mode{};
  SDL_GetCurrentDisplayMode(index, &mode);
  return mode;
}

void verify(const SDL_DisplayMode& expected, const cen::display_mode& mode)
{
  ASSERT_EQ(expected.refresh_rate, mode.refresh_rate());

  ASSERT_EQ(expected.w, mode.width());
  ASSERT_EQ(expected.h, mode.height());

  ASSERT_EQ(expected.w, mode.size().width);
  ASSERT_EQ(expected.h, mode.size().height);

  ASSERT_EQ(expected.format, cen::to_underlying(mode.format()));
  ASSERT_EQ(expected.driverdata, mode.driver_data());
}

}  // namespace

TEST(DisplayMode, InvalidDisplayIndex)
{
  ASSERT_THROW(cen::display_mode::desktop(cen::display_count()), cen::sdl_error);
  ASSERT_THROW(cen::display_mode::current(cen::display_count()), cen::sdl_error);
}

TEST(DisplayMode, Desktop)
{
  const auto expected = get_sdl_desktop_display_mode(0);
  const auto desktop = cen::display_mode::desktop();
  verify(expected, desktop);
}

TEST(DisplayMode, Current)
{
  const auto expected = get_sdl_current_display_mode(0);
  const auto current = cen::display_mode::current();
  verify(expected, current);
}
