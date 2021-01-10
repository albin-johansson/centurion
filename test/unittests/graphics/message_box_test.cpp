#include "message_box.hpp"

#include <gtest/gtest.h>

#include <type_traits>

#include "colors.hpp"

static_assert(std::is_final_v<cen::message_box>);
static_assert(std::is_default_constructible_v<cen::message_box>);

TEST(MessageBox, TitleMessageConstructor)
{
  const cen::message_box mb{"foo", "bar"};
  EXPECT_EQ("foo", mb.get_title());
  EXPECT_EQ("bar", mb.get_message());
}

TEST(MessageBox, AddButton)
{
  cen::message_box mb;

  constexpr auto id{3};
  mb.add_button(id, "Foo");

  EXPECT_TRUE(mb.has_button(id));
}

TEST(MessageBox, SetTitle)
{
  cen::message_box mb;

  mb.set_title("foobar");
  EXPECT_EQ("foobar", mb.get_title());
}

TEST(MessageBox, SetMessage)
{
  cen::message_box mb;

  mb.set_message("barfoo");
  EXPECT_EQ("barfoo", mb.get_message());
}

TEST(MessageBox, SetColorScheme)
{
  cen::message_box mb;
  cen::message_box::color_scheme scheme;
  EXPECT_NO_THROW(mb.set_color_scheme(scheme));
}

TEST(MessageBox, SetType)
{
  using type = cen::message_box::type;
  cen::message_box mb;

  mb.set_type(type::information);
  EXPECT_EQ(type::information, mb.get_type());

  mb.set_type(type::warning);
  EXPECT_EQ(type::warning, mb.get_type());

  mb.set_type(type::error);
  EXPECT_EQ(type::error, mb.get_type());
}

TEST(MessageBox, SetButtonOrder)
{
  using order = cen::message_box::button_order;
  cen::message_box mb;

  mb.set_button_order(order::left_to_right);
  EXPECT_EQ(order::left_to_right, mb.get_button_order());

  mb.set_button_order(order::right_to_left);
  EXPECT_EQ(order::right_to_left, mb.get_button_order());
}

TEST(MessageBox, HasButton)
{
  cen::message_box mb;

  constexpr auto id = 7;
  EXPECT_FALSE(mb.has_button(id));

  mb.add_button(id, "foo");
  EXPECT_TRUE(mb.has_button(id));
}

TEST(MessageBox, GetTitle)
{
  const cen::message_box mb;
  EXPECT_EQ("Message box", mb.get_title());
}

TEST(MessageBox, GetMessage)
{
  const cen::message_box mb;
  EXPECT_EQ("N/A", mb.get_message());
}

TEST(MessageBox, GetType)
{
  const cen::message_box mb;
  EXPECT_EQ(cen::message_box::type::information, mb.get_type());
}

TEST(MessageBox, GetButtonOrder)
{
  const cen::message_box mb;
  EXPECT_EQ(cen::message_box::button_order::left_to_right,
            mb.get_button_order());
}

TEST(MessageBox, ButtonOrderEnum)
{
  using order = cen::message_box::button_order;
  EXPECT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
            static_cast<int>(order::left_to_right));
  EXPECT_EQ(SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT,
            static_cast<int>(order::right_to_left));
}

TEST(MessageBox, TypeEnum)
{
  using type = cen::message_box::type;
  EXPECT_EQ(SDL_MESSAGEBOX_INFORMATION, static_cast<int>(type::information));
  EXPECT_EQ(SDL_MESSAGEBOX_WARNING, static_cast<int>(type::warning));
  EXPECT_EQ(SDL_MESSAGEBOX_ERROR, static_cast<int>(type::error));
}

TEST(MessageBox, ColorSchemeClass)
{
  {  // Defaults
    cen::message_box::color_scheme scheme;
    const auto* ptr = scheme.get();

    using cen::colors::white;
    EXPECT_EQ(white, ptr->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
    EXPECT_EQ(white, ptr->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
    EXPECT_EQ(white, ptr->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]);
    EXPECT_EQ(white, ptr->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]);
    EXPECT_EQ(white, ptr->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
  }

  {  // Custom scheme
    cen::message_box::color_scheme scheme;

    const auto check = [&](cen::message_box::color_id id,
                           const cen::color& color) {
      scheme.set_color(id, color);
      EXPECT_EQ(color, scheme.get()->colors[static_cast<cen::u32>(id)]);
    };

    check(cen::message_box::color_id::background, cen::colors::pink);
    check(cen::message_box::color_id::text, cen::colors::salmon);
    check(cen::message_box::color_id::button_background, cen::colors::violet);
    check(cen::message_box::color_id::button_border, cen::colors::alice_blue);
    check(cen::message_box::color_id::button_selected, cen::colors::wheat);
  }
}

TEST(MessageBox, DefaultButtonEnum)
{
  using button = cen::message_box::default_button;

  EXPECT_EQ(button::return_key, SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT);
  EXPECT_EQ(button::escape_key, SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT);

  EXPECT_EQ(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, button::return_key);
  EXPECT_EQ(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, button::escape_key);

  EXPECT_NE(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, button::escape_key);
}

TEST(MessageBox, ColorIdEnum)
{
  using id = cen::message_box::color_id;

  EXPECT_EQ(id::button_selected, SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED);
  EXPECT_EQ(id::button_background, SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  EXPECT_EQ(id::button_border, SDL_MESSAGEBOX_COLOR_BUTTON_BORDER);
  EXPECT_EQ(id::background, SDL_MESSAGEBOX_COLOR_BACKGROUND);

  EXPECT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED, id::button_selected);
  EXPECT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND, id::button_background);
  EXPECT_EQ(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER, id::button_border);
  EXPECT_EQ(SDL_MESSAGEBOX_COLOR_BACKGROUND, id::background);

  EXPECT_NE(id::background, SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND);
  EXPECT_NE(SDL_MESSAGEBOX_COLOR_BUTTON_BORDER, id::button_selected);
}
