#include "system/shared_object.hpp"

#include <gtest/gtest.h>

TEST(SharedObject, Constructor)
{
  EXPECT_THROW(cen::shared_object{"foo"}, cen::sdl_error);
}