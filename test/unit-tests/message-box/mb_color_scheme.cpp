#include <gtest/gtest.h>

#include "message_box.hpp"

TEST(MessageBoxColorScheme, Defaults)
{
  const cen::message_box_color_scheme scheme;

  const auto* data = scheme.data();
  const auto color = cen::colors::white;

  ASSERT_EQ(color, cen::color{data->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]});
  ASSERT_EQ(color, cen::color{data->colors[SDL_MESSAGEBOX_COLOR_TEXT]});
  ASSERT_EQ(color, cen::color{data->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER]});
  ASSERT_EQ(color, cen::color{data->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND]});
  ASSERT_EQ(color, cen::color{data->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]});
}

TEST(MessageBoxColorScheme, Custom)
{
  cen::message_box_color_scheme scheme;

  const auto check = [&](const cen::message_box_color_type type, const cen::color& color) {
    scheme.set_color(type, color);
    ASSERT_EQ(color, cen::color{scheme.data()->colors[cen::to_underlying(type)]});
  };

  check(cen::message_box_color_type::text, cen::colors::salmon);
  check(cen::message_box_color_type::background, cen::colors::pink);
  check(cen::message_box_color_type::button_background, cen::colors::violet);
  check(cen::message_box_color_type::button_border, cen::colors::alice_blue);
  check(cen::message_box_color_type::button_selected, cen::colors::wheat);
}
