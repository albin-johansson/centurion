#include <gtest/gtest.h>

#include "common.hpp"

using foo_type = cen::ulonglong;
using bar_type = char;

enum class foo : foo_type {
  a = 27,
  b = 42,
  c = 123
};

enum class bar : bar_type {
  a = 'a',
  b = '1',
  c = 'x'
};

static_assert(std::is_same_v<foo_type, decltype(cen::to_underlying(foo::a))>);
static_assert(std::is_same_v<bar_type, decltype(cen::to_underlying(bar::a))>);

TEST(to_underlying, to_underlying)
{
  ASSERT_EQ(27u, cen::to_underlying(foo::a));
  ASSERT_EQ(42u, cen::to_underlying(foo::b));
  ASSERT_EQ(123u, cen::to_underlying(foo::c));

  ASSERT_EQ('a', cen::to_underlying(bar::a));
  ASSERT_EQ('1', cen::to_underlying(bar::b));
  ASSERT_EQ('x', cen::to_underlying(bar::c));
}
