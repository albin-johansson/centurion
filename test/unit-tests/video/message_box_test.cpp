#include "video/message_box.hpp"

#include <gtest/gtest.h>

#include <type_traits>

#include "core/common.hpp"
#include "video/colors.hpp"

static_assert(std::is_final_v<cen::message_box>);
static_assert(std::is_default_constructible_v<cen::message_box>);

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
  cen::message_box::color_scheme scheme;
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

  mb.set_button_order(cen::button_order::left_to_right);
  ASSERT_EQ(cen::button_order::left_to_right, mb.get_button_order());

  mb.set_button_order(cen::button_order::right_to_left);
  ASSERT_EQ(cen::button_order::right_to_left, mb.get_button_order());
}

TEST(MessageBox, HasButton)
{
  cen::message_box mb;

  constexpr auto id = 7;
  ASSERT_FALSE(mb.has_button(id));

  mb.add_button(id, "foo");
  ASSERT_TRUE(mb.has_button(id));
}

TEST(MessageBox, Title)
{
  const cen::message_box mb;
  ASSERT_EQ("Message box", mb.title());
}

TEST(MessageBox, Message)
{
  const cen::message_box mb;
  ASSERT_EQ("n/a", mb.message());
}

TEST(MessageBox, GetType)
{
  const cen::message_box mb;
  ASSERT_EQ(cen::message_box_type::information, mb.type());
}

TEST(MessageBox, GetButtonOrder)
{
  const cen::message_box mb;
  ASSERT_EQ(cen::button_order::left_to_right, mb.get_button_order());
}

TEST(MessageBox, ColorSchemeClass)
{
  {  // Defaults
    cen::message_box::color_scheme scheme;
    const auto* ptr = scheme.get();

    ASSERT_EQ(cen::colors::white, cen::Color{ptr->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]});
    ASSERT_EQ(cen::colors::white, cen::Color{ptr->colors[SDL_MESSAGEBOX_COLOR_TEXT]});
    ASSERT_EQ(cen::colors::white, cen::Color{ptr->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]});
    ASSERT_EQ(cen::colors::white,
              cen::Color{ptr->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]});
    ASSERT_EQ(cen::colors::white,
              cen::Color{ptr->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]});
  }

  {  // Custom scheme
    cen::message_box::color_scheme scheme;

    const auto check = [&](cen::message_box::color_id id, const cen::Color& color) {
      scheme.set_color(id, color);
      ASSERT_EQ(color, cen::Color{scheme.get()->colors[cen::ToUnderlying(id)]});
    };

    check(cen::message_box::color_id::background, cen::colors::pink);
    check(cen::message_box::color_id::text, cen::colors::salmon);
    check(cen::message_box::color_id::button_background, cen::colors::violet);
    check(cen::message_box::color_id::button_border, cen::colors::alice_blue);
    check(cen::message_box::color_id::button_selected, cen::colors::wheat);
  }
}
