#include "video/graphics_drivers.hpp"

#include <gtest/gtest.h>

TEST(GraphicsDrivers, RenderDriverCount)
{
  EXPECT_EQ(SDL_GetNumRenderDrivers(), cen::render_driver_count());
}

TEST(GraphicsDrivers, VideoDriverCount)
{
  EXPECT_EQ(SDL_GetNumVideoDrivers(), cen::video_driver_count());
}
