#include <gtest/gtest.h>

#include "system/system.hpp"

TEST(Clipboard, HasClipboardText)
{
  ASSERT_TRUE(cen::set_clipboard_text(""));
  ASSERT_FALSE(cen::has_clipboard_text());

  ASSERT_TRUE(cen::set_clipboard_text("foobar"));
  ASSERT_TRUE(cen::has_clipboard_text());
}

TEST(Clipboard, SetClipboardText)
{
  ASSERT_TRUE(cen::set_clipboard_text("foo"));
  ASSERT_EQ(cen::get_clipboard_text(), "foo");

  using namespace std::string_literals;
  ASSERT_TRUE(cen::set_clipboard_text("bar"s));
  ASSERT_EQ(cen::get_clipboard_text(), "bar");
}
