#include "common.hpp"

#include <gtest/gtest.h>

#include <type_traits>

static_assert(std::has_virtual_destructor_v<cen::Error>);
static_assert(std::is_default_constructible_v<cen::Error>);
static_assert(std::is_nothrow_move_constructible_v<cen::Error>);
static_assert(std::is_nothrow_destructible_v<cen::Error>);

TEST(Exception, CStringConstructor)
{
  const cen::Error exception{"Foo"};
  ASSERT_STREQ("Foo", exception.what());
}
