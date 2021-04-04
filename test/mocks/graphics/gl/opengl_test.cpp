#include "video/gl/opengl.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

// clang-format off
extern "C" {
FAKE_VOID_FUNC(SDL_GL_SwapWindow, SDL_Window*)
FAKE_VALUE_FUNC(int, SDL_GL_SetSwapInterval, int)
FAKE_VALUE_FUNC(int, SDL_GL_GetSwapInterval)
}
// clang-format on

class OpenGLTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GL_SwapWindow)
    RESET_FAKE(SDL_GL_SetSwapInterval)
    RESET_FAKE(SDL_GL_GetSwapInterval)
  }

  cen::window_handle m_window{nullptr};
};

TEST_F(OpenGLTest, Swap)
{
  std::array values{cen::u32{SDL_WINDOW_OPENGL}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  EXPECT_NO_FATAL_FAILURE(cen::gl::swap(m_window));
  EXPECT_EQ(1, SDL_GL_SwapWindow_fake.call_count);
}

TEST_F(OpenGLTest, SetSwapInterval)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GL_SetSwapInterval, values.data(), cen::isize(values));

  EXPECT_FALSE(cen::gl::set_swap_interval(1));
  EXPECT_TRUE(cen::gl::set_swap_interval(1));
  EXPECT_EQ(2, SDL_GL_SetSwapInterval_fake.call_count);
}

TEST_F(OpenGLTest, SwapInterval)
{
  const auto interval [[maybe_unused]] = cen::gl::swap_interval();
  EXPECT_EQ(1, SDL_GL_GetSwapInterval_fake.call_count);
}
