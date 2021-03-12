#include "clipboard.hpp"

#include <gtest/gtest.h>

TEST(Clipboard, HasText)
{
  EXPECT_TRUE(cen::clipboard::set_text(""));
  EXPECT_FALSE(cen::clipboard::has_text());

  EXPECT_TRUE(cen::clipboard::set_text("foobar"));
  EXPECT_TRUE(cen::clipboard::has_text());
}

TEST(Clipboard, SetText)
{
  EXPECT_TRUE(cen::clipboard::set_text("foo"));
  EXPECT_EQ(cen::clipboard::get_text(), "foo");

  using namespace std::string_literals;
  EXPECT_TRUE(cen::clipboard::set_text("bar"s));
  EXPECT_EQ(cen::clipboard::get_text(), "bar");
}
