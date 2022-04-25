#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/window.hpp"

TEST(WindowFlags, Values)
{
  ASSERT_EQ(SDL_WINDOW_FULLSCREEN, to_underlying(cen::window::fullscreen));
  ASSERT_EQ(SDL_WINDOW_FULLSCREEN_DESKTOP, to_underlying(cen::window::fullscreen_desktop));

  ASSERT_EQ(SDL_WINDOW_SHOWN, to_underlying(cen::window::shown));
  ASSERT_EQ(SDL_WINDOW_HIDDEN, to_underlying(cen::window::hidden));
  ASSERT_EQ(SDL_WINDOW_MINIMIZED, to_underlying(cen::window::minimized));
  ASSERT_EQ(SDL_WINDOW_MAXIMIZED, to_underlying(cen::window::maximized));

  ASSERT_EQ(SDL_WINDOW_BORDERLESS, to_underlying(cen::window::borderless));
  ASSERT_EQ(SDL_WINDOW_RESIZABLE, to_underlying(cen::window::resizable));
  ASSERT_EQ(SDL_WINDOW_SKIP_TASKBAR, to_underlying(cen::window::skip_taskbar));

  ASSERT_EQ(SDL_WINDOW_INPUT_GRABBED, to_underlying(cen::window::input_grabbed));
  ASSERT_EQ(SDL_WINDOW_INPUT_FOCUS, to_underlying(cen::window::input_focus));
  ASSERT_EQ(SDL_WINDOW_MOUSE_FOCUS, to_underlying(cen::window::mouse_focus));
  ASSERT_EQ(SDL_WINDOW_MOUSE_CAPTURE, to_underlying(cen::window::mouse_capture));

  ASSERT_EQ(SDL_WINDOW_ALLOW_HIGHDPI, to_underlying(cen::window::allow_high_dpi));
  ASSERT_EQ(SDL_WINDOW_ALWAYS_ON_TOP, to_underlying(cen::window::always_on_top));

  ASSERT_EQ(SDL_WINDOW_FOREIGN, to_underlying(cen::window::foreign));
  ASSERT_EQ(SDL_WINDOW_UTILITY, to_underlying(cen::window::utility));
  ASSERT_EQ(SDL_WINDOW_TOOLTIP, to_underlying(cen::window::tooltip));
  ASSERT_EQ(SDL_WINDOW_POPUP_MENU, to_underlying(cen::window::popup_menu));

  ASSERT_EQ(SDL_WINDOW_OPENGL, to_underlying(cen::window::opengl));
  ASSERT_EQ(SDL_WINDOW_VULKAN, to_underlying(cen::window::vulkan));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(SDL_WINDOW_METAL, to_underlying(cen::window::metal));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}
