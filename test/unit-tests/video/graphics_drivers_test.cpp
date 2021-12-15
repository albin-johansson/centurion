#include <gtest/gtest.h>

#include "render.hpp"

TEST(GraphicsDrivers, RenderDriverCount)
{
  ASSERT_EQ(SDL_GetNumRenderDrivers(), cen::GetRenderDrivers());
}

TEST(GraphicsDrivers, VideoDriverCount)
{
  ASSERT_EQ(SDL_GetNumVideoDrivers(), cen::GetVideoDrivers());
}
