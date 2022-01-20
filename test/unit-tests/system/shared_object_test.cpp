#include <gtest/gtest.h>

#include "centurion/system.hpp"

TEST(SharedObject, Constructor)
{
  ASSERT_THROW(cen::shared_object{"foo"}, cen::sdl_error);
}