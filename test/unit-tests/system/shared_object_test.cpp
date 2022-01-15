#include <gtest/gtest.h>

#include "system.hpp"

TEST(SharedObject, Constructor)
{
  ASSERT_THROW(cen::SharedObject{"foo"}, cen::sdl_error);
}