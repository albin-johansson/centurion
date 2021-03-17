#include "video/graphics_drivers.hpp"

#include <gtest/gtest.h>

TEST(GraphicsDrivers, NumRenderDrivers)
{
  EXPECT_EQ(SDL_GetNumRenderDrivers(), cen::num_render_drivers());
}

TEST(GraphicsDrivers, NumVideoDrivers)
{
  EXPECT_EQ(SDL_GetNumVideoDrivers(), cen::num_video_drivers());
}
