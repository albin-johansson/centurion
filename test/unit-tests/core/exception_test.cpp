#include "misc/exception.hpp"

#include <gtest/gtest.h>

#include <type_traits>

static_assert(std::has_virtual_destructor_v<cen::cen_error>);
static_assert(std::is_default_constructible_v<cen::cen_error>);
static_assert(std::is_nothrow_move_constructible_v<cen::cen_error>);
static_assert(std::is_nothrow_destructible_v<cen::cen_error>);

TEST(Exception, CStringConstructor)
{
  const cen::cen_error exception{"Foo"};
  EXPECT_STREQ("Foo", exception.what());
}
