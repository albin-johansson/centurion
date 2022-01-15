#include <gtest/gtest.h>

#include "message_box.hpp"

TEST(MessageBoxColorScheme, Defaults)
{
  const cen::MessageBoxColorScheme scheme;

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
  cen::MessageBoxColorScheme scheme;

  const auto check = [&](const cen::MessageBoxColorType type, const cen::color& color) {
    scheme.SetColor(type, color);
    ASSERT_EQ(color, cen::color{scheme.data()->colors[cen::ToUnderlying(type)]});
  };

  check(cen::MessageBoxColorType::Text, cen::colors::salmon);
  check(cen::MessageBoxColorType::Background, cen::colors::pink);
  check(cen::MessageBoxColorType::ButtonBackground, cen::colors::violet);
  check(cen::MessageBoxColorType::ButtonBorder, cen::colors::alice_blue);
  check(cen::MessageBoxColorType::ButtonSelected, cen::colors::wheat);
}
