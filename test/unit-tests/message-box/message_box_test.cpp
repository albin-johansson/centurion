#include "message_box.hpp"

#include <gtest/gtest.h>

#include <type_traits>

#include "color.hpp"

static_assert(std::is_final_v<cen::message_box>);
static_assert(std::is_default_constructible_v<cen::message_box>);

TEST(MessageBox, Defaults)
{
  const cen::message_box mb;

  ASSERT_EQ("Message box", mb.title());
  ASSERT_TRUE(mb.message().empty());

  ASSERT_EQ(cen::message_box_type::information, mb.type());
  ASSERT_EQ(cen::message_box_button_order::left_to_right, mb.button_order());

  ASSERT_EQ(cen::message_box_type::information, cen::message_box::default_type());
  ASSERT_EQ(cen::message_box_button_order::left_to_right, cen::message_box::default_order());
}

TEST(MessageBox, TitleMessageConstructor)
{
  const cen::message_box mb{"foo", "bar"};
  ASSERT_EQ("foo", mb.title());
  ASSERT_EQ("bar", mb.message());
}

TEST(MessageBox, AddButton)
{
  cen::message_box mb;

  constexpr auto id{3};
  mb.add_button(id, "Foo");

  ASSERT_TRUE(mb.has_button(id));
}

TEST(MessageBox, SetTitle)
{
  cen::message_box mb;

  mb.set_title("foobar");
  ASSERT_EQ("foobar", mb.title());
}

TEST(MessageBox, SetMessage)
{
  cen::message_box mb;

  mb.set_message("barfoo");
  ASSERT_EQ("barfoo", mb.message());
}

TEST(MessageBox, SetColorScheme)
{
  cen::message_box mb;
  cen::message_box_color_scheme scheme;
  ASSERT_NO_THROW(mb.set_color_scheme(scheme));
}

TEST(MessageBox, SetType)
{
  cen::message_box mb;

  mb.set_type(cen::message_box_type::information);
  ASSERT_EQ(cen::message_box_type::information, mb.type());

  mb.set_type(cen::message_box_type::warning);
  ASSERT_EQ(cen::message_box_type::warning, mb.type());

  mb.set_type(cen::message_box_type::error);
  ASSERT_EQ(cen::message_box_type::error, mb.type());
}

TEST(MessageBox, SetButtonOrder)
{
  cen::message_box mb;

  mb.set_button_order(cen::message_box_button_order::left_to_right);
  ASSERT_EQ(cen::message_box_button_order::left_to_right, mb.button_order());

  mb.set_button_order(cen::message_box_button_order::right_to_left);
  ASSERT_EQ(cen::message_box_button_order::right_to_left, mb.button_order());
}

TEST(MessageBox, HasButton)
{
  cen::message_box mb;

  constexpr auto id = 7;
  ASSERT_FALSE(mb.has_button(id));

  mb.add_button(id, "foo");
  ASSERT_TRUE(mb.has_button(id));
}
