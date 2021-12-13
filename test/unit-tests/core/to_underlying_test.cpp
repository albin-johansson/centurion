#include <gtest/gtest.h>

#include "core/common.hpp"

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

static_assert(std::is_same_v<foo_type, decltype(cen::ToUnderlying(foo::a))>);
static_assert(std::is_same_v<bar_type, decltype(cen::ToUnderlying(bar::a))>);

TEST(ToUnderlying, ToUnderlying)
{
  ASSERT_EQ(27u, cen::ToUnderlying(foo::a));
  ASSERT_EQ(42u, cen::ToUnderlying(foo::b));
  ASSERT_EQ(123u, cen::ToUnderlying(foo::c));

  ASSERT_EQ('a', cen::ToUnderlying(bar::a));
  ASSERT_EQ('1', cen::ToUnderlying(bar::b));
  ASSERT_EQ('x', cen::ToUnderlying(bar::c));
}
