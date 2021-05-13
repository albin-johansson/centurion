#include "system/clipboard.hpp"

#include <gtest/gtest.h>

TEST(Clipboard, HasText)
{
  ASSERT_TRUE(cen::clipboard::set_text(""));
  ASSERT_FALSE(cen::clipboard::has_text());

  ASSERT_TRUE(cen::clipboard::set_text("foobar"));
  ASSERT_TRUE(cen::clipboard::has_text());
}

TEST(Clipboard, SetText)
{
  ASSERT_TRUE(cen::clipboard::set_text("foo"));
  ASSERT_EQ(cen::clipboard::get_text(), "foo");

  using namespace std::string_literals;
  ASSERT_TRUE(cen::clipboard::set_text("bar"s));
  ASSERT_EQ(cen::clipboard::get_text(), "bar");
}
