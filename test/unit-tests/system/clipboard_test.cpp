#include <gtest/gtest.h>

#include "system.hpp"

TEST(Clipboard, HasClipboard)
{
  ASSERT_TRUE(cen::set_clipboard(""));
  ASSERT_FALSE(cen::has_clipboard());

  ASSERT_TRUE(cen::set_clipboard("foobar"));
  ASSERT_TRUE(cen::has_clipboard());
}

TEST(Clipboard, SetClipboard)
{
  ASSERT_TRUE(cen::set_clipboard("foo"));
  ASSERT_EQ(cen::get_clipboard(), "foo");

  using namespace std::string_literals;
  ASSERT_TRUE(cen::set_clipboard("bar"s));
  ASSERT_EQ(cen::get_clipboard(), "bar");
}
