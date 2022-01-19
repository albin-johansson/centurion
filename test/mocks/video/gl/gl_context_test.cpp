#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"
#include "opengl.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_GL_MakeCurrent, SDL_Window*, SDL_GLContext)
}

class OpenGLContextTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GL_MakeCurrent)
  }

  cen::GLContextHandle m_context{nullptr};
};

TEST_F(OpenGLContextTest, Construction)
{
  ASSERT_THROW(cen::GLContext{nullptr}, cen::exception);
  ASSERT_NO_THROW(cen::GLContextHandle{nullptr});
}

TEST_F(OpenGLContextTest, MakeCurrent)
{
  std::array flags{Uint32{cen::window::opengl}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, flags.data(), cen::isize(flags));

  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GL_MakeCurrent, values.data(), cen::isize(values));

  cen::window_handle window{nullptr};
  ASSERT_EQ(cen::failure, m_context.MakeCurrent(window));
  ASSERT_EQ(cen::success, m_context.MakeCurrent(window));
  ASSERT_EQ(2u, SDL_GL_MakeCurrent_fake.call_count);
}
