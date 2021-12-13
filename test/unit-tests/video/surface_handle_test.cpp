#include <gtest/gtest.h>

#include "video/surface.hpp"

namespace {
inline constexpr auto path = "resources/panda.png";
}

TEST(SurfaceHandle, Constructor)
{
  ASSERT_FALSE(cen::SurfaceHandle{nullptr});

  const cen::Surface surface{path};
  cen::SurfaceHandle handle{surface.get()};

  ASSERT_TRUE(handle);
}
