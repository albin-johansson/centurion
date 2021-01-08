#include "exception.hpp"

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

static_assert(std::has_virtual_destructor_v<cen::exception>);
static_assert(std::is_default_constructible_v<cen::exception>);
static_assert(std::is_nothrow_move_constructible_v<cen::exception>);
static_assert(std::is_nothrow_destructible_v<cen::exception>);

TEST(Exception, CStringConstructor)
{
  {  // Null string
    cen::exception exception{nullptr};
    EXPECT_STREQ("N/A", exception.what());
  }

  {  // Normal argument
    const cen::exception exception{"Foo"};
    EXPECT_STREQ("Foo", exception.what());
  }
}

TEST(Exception, StdStringConstructor)
{
  const std::string str{"foobar"};
  const cen::exception exception{str};
  EXPECT_EQ(str, exception.what());
}
