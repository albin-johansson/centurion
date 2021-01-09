#include "thread.hpp"

#include <gtest/gtest.h>

#include "core_mocks.hpp"
#include "thread_mocks.hpp"

// See SDL_thread.h
#define SDL_CreateThread(fn, name, data)                       \
  SDL_CreateThread(fn,                                         \
                   name,                                       \
                   data,                                       \
                   (pfnSDL_CurrentBeginThread)SDL_beginthread, \
                   (pfnSDL_CurrentEndThread)SDL_endthread)

class ThreadTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();
    mocks::reset_thread();
  }
};

TEST_F(ThreadTest, Constructor)
{
  auto dummy = [](void*) {
    return 0;
  };
  EXPECT_THROW(cen::thread{dummy}, cen::sdl_error);
}
