#include <gtest/gtest.h>

#include "system.hpp"

TEST(Clipboard, HasClipboard)
{
  ASSERT_TRUE(cen::SetClipboard(""));
  ASSERT_FALSE(cen::HasClipboard());

  ASSERT_TRUE(cen::SetClipboard("foobar"));
  ASSERT_TRUE(cen::HasClipboard());
}

TEST(Clipboard, SetClipboard)
{
  ASSERT_TRUE(cen::SetClipboard("foo"));
  ASSERT_EQ(cen::GetClipboard(), "foo");

  using namespace std::string_literals;
  ASSERT_TRUE(cen::SetClipboard("bar"s));
  ASSERT_EQ(cen::GetClipboard(), "bar");
}
