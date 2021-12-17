#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"
#include "window.hpp"

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
  auto window [[maybe_unused]] = cen::GetGrabbedWindow();
  ASSERT_EQ(1u, SDL_GetGrabbedWindow_fake.call_count);
}

TEST_F(WindowUtilsTest, MouseFocusWindow)
{
  auto window [[maybe_unused]] = cen::GetMouseFocusWindow();
  ASSERT_EQ(1u, SDL_GetMouseFocus_fake.call_count);
}

TEST_F(WindowUtilsTest, KeyboardFocusWindow)
{
  auto window [[maybe_unused]] = cen::GetKeyboardFocusWindow();
  ASSERT_EQ(1u, SDL_GetKeyboardFocus_fake.call_count);
}

TEST_F(WindowUtilsTest, GetWindow)
{
  auto window [[maybe_unused]] = cen::GetWindow(0);
  ASSERT_EQ(1u, SDL_GetWindowFromID_fake.call_count);
}

TEST_F(WindowUtilsTest, GetRenderer)
{
  cen::WindowHandle window{nullptr};
  auto renderer [[maybe_unused]] = cen::GetRenderer(window);
  ASSERT_EQ(1u, SDL_GetRenderer_fake.call_count);
}
