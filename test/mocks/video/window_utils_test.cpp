#include <fff.h>
#include <gtest/gtest.h>

#include "centurion/window.hpp"
#include "core_mocks.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(SDL_Window*, SDL_GetGrabbedWindow)
  FAKE_VALUE_FUNC(SDL_Window*, SDL_GetMouseFocus)
  FAKE_VALUE_FUNC(SDL_Window*, SDL_GetKeyboardFocus)
  FAKE_VALUE_FUNC(SDL_Window*, SDL_GetWindowFromID, Uint32)
  FAKE_VALUE_FUNC(SDL_Renderer*, SDL_GetRenderer, SDL_Window*)
}

class WindowUtilsTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GetGrabbedWindow)
    RESET_FAKE(SDL_GetMouseFocus)
    RESET_FAKE(SDL_GetKeyboardFocus)
    RESET_FAKE(SDL_GetWindowFromID)
    RESET_FAKE(SDL_GetRenderer)
  }
};

TEST_F(WindowUtilsTest, GetGrabbedWindow)
{
  auto window [[maybe_unused]] = cen::get_grabbed_window();
  ASSERT_EQ(1u, SDL_GetGrabbedWindow_fake.call_count);
}

TEST_F(WindowUtilsTest, GetMouseFocusWindow)
{
  auto window [[maybe_unused]] = cen::get_mouse_focus_window();
  ASSERT_EQ(1u, SDL_GetMouseFocus_fake.call_count);
}

TEST_F(WindowUtilsTest, GetKeyboardFocusWindow)
{
  auto window [[maybe_unused]] = cen::get_keyboard_focus_window();
  ASSERT_EQ(1u, SDL_GetKeyboardFocus_fake.call_count);
}

TEST_F(WindowUtilsTest, GetWindow)
{
  auto window [[maybe_unused]] = cen::get_window(0);
  ASSERT_EQ(1u, SDL_GetWindowFromID_fake.call_count);
}

TEST_F(WindowUtilsTest, GetRenderer)
{
  cen::window_handle window{nullptr};
  auto renderer [[maybe_unused]] = window.get_renderer();
  ASSERT_EQ(1u, SDL_GetRenderer_fake.call_count);
}
