#include "message_box.hpp"

#include <gtest/gtest.h>

#include <type_traits>

#include "color.hpp"

static_assert(std::is_final_v<cen::MessageBox>);
static_assert(std::is_default_constructible_v<cen::MessageBox>);

TEST(MessageBox, Defaults)
{
  const cen::MessageBox mb;

  ASSERT_EQ("Message box", mb.GetTitle());
  ASSERT_EQ("N/A", mb.GetMessage());

  ASSERT_EQ(cen::MessageBoxType::Information, mb.GetType());
  ASSERT_EQ(cen::MessageBoxButtonOrder::LeftToRight, mb.GetButtonOrder());

  ASSERT_EQ(cen::MessageBoxType::Information, cen::MessageBox::GetDefaultType());
  ASSERT_EQ(cen::MessageBoxButtonOrder::LeftToRight, cen::MessageBox::GetDefaultOrder());
}

TEST(MessageBox, TitleMessageConstructor)
{
  const cen::MessageBox mb{"foo", "bar"};
  ASSERT_EQ("foo", mb.GetTitle());
  ASSERT_EQ("bar", mb.GetMessage());
}

TEST(MessageBox, AddButton)
{
  cen::MessageBox mb;

  constexpr auto id{3};
  mb.AddButton(id, "Foo");

  ASSERT_TRUE(mb.HasButton(id));
}

TEST(MessageBox, SetTitle)
{
  cen::MessageBox mb;

  mb.SetTitle("foobar");
  ASSERT_EQ("foobar", mb.GetTitle());
}

TEST(MessageBox, SetMessage)
{
  cen::MessageBox mb;

  mb.SetMessage("barfoo");
  ASSERT_EQ("barfoo", mb.GetMessage());
}

TEST(MessageBox, SetColorScheme)
{
  cen::MessageBox mb;
  cen::MessageBoxColorScheme scheme;
  ASSERT_NO_THROW(mb.SetColorScheme(scheme));
}

TEST(MessageBox, SetType)
{
  cen::MessageBox mb;

  mb.SetType(cen::MessageBoxType::Information);
  ASSERT_EQ(cen::MessageBoxType::Information, mb.GetType());

  mb.SetType(cen::MessageBoxType::Warning);
  ASSERT_EQ(cen::MessageBoxType::Warning, mb.GetType());

  mb.SetType(cen::MessageBoxType::Error);
  ASSERT_EQ(cen::MessageBoxType::Error, mb.GetType());
}

TEST(MessageBox, SetButtonOrder)
{
  cen::MessageBox mb;

  mb.SetButtonOrder(cen::MessageBoxButtonOrder::LeftToRight);
  ASSERT_EQ(cen::MessageBoxButtonOrder::LeftToRight, mb.GetButtonOrder());

  mb.SetButtonOrder(cen::MessageBoxButtonOrder::RightToLeft);
  ASSERT_EQ(cen::MessageBoxButtonOrder::RightToLeft, mb.GetButtonOrder());
}

TEST(MessageBox, HasButton)
{
  cen::MessageBox mb;

  constexpr auto id = 7;
  ASSERT_FALSE(mb.HasButton(id));

  mb.AddButton(id, "foo");
  ASSERT_TRUE(mb.HasButton(id));
}
