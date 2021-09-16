#include "video/opengl/gl_library.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core/integers.hpp"
#include "core_mocks.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_GL_LoadLibrary, const char*)
  FAKE_VALUE_FUNC(void*, SDL_GL_GetProcAddress, const char*)
  FAKE_VOID_FUNC(SDL_GL_UnloadLibrary)
}

class OpenGLLibraryTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GL_LoadLibrary)
    RESET_FAKE(SDL_GL_GetProcAddress)
    RESET_FAKE(SDL_GL_UnloadLibrary)
  }
};

TEST_F(OpenGLLibraryTest, Construction)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_GL_LoadLibrary, values.data(), cen::isize(values));

  ASSERT_THROW(cen::gl_library library, cen::sdl_error);
  ASSERT_NO_THROW(cen::gl_library library);
}

TEST_F(OpenGLLibraryTest, AddressOf)
{
  std::array values{0};
  SET_RETURN_SEQ(SDL_GL_LoadLibrary, values.data(), cen::isize(values));

  cen::gl_library library;
  const auto* address [[maybe_unused]] = library.address_of("foo");

  ASSERT_EQ(1, SDL_GL_GetProcAddress_fake.call_count);
}