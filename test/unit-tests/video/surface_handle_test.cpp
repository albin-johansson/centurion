#include <gtest/gtest.h>

#include "video/surface.hpp"

namespace {
inline constexpr auto path = "resources/panda.png";
}

TEST(SurfaceHandle, Constructor)
{
  EXPECT_FALSE(cen::surface_handle{nullptr});

  const cen::surface surface{path};
  cen::surface_handle handle{surface.get()};

  EXPECT_TRUE(handle);
}
