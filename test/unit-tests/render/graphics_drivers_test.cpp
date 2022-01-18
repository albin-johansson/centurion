#include <gtest/gtest.h>

#include "render.hpp"

TEST(GraphicsDrivers, RenderDriverCount)
{
  ASSERT_EQ(SDL_GetNumRenderDrivers(), cen::render_driver_count());
}

TEST(GraphicsDrivers, VideoDriverCount)
{
  ASSERT_EQ(SDL_GetNumVideoDrivers(), cen::video_driver_count());
}
