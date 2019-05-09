#include <pch.h>

TEST(Color, ctor) {
  int overflow = Color::MAX_VAL + 11294;

  EXPECT_NO_THROW(Color(overflow, 0, 0, 0));
  EXPECT_NO_THROW(Color(0, overflow, 0, 0));
  EXPECT_NO_THROW(Color(0, 0, overflow, 0));
  EXPECT_NO_THROW(Color(0, 0, 0, overflow));
}

TEST(Color, getters) {
  Uint8 red = 0xFD;
  Uint8 green = 0x3A;
  Uint8 blue = 0x8E;
  Uint8 alpha = 0x39;

  Color color = Color(red, green, blue, alpha);

  EXPECT_EQ(color.GetRed(), red);
  EXPECT_EQ(color.GetGreen(), green);
  EXPECT_EQ(color.GetBlue(), blue);
  EXPECT_EQ(color.GetAlpha(), alpha);

  SDL_Color sdlColor = color.GetSDLVersion();
  EXPECT_EQ(color.GetRed(), sdlColor.r);
  EXPECT_EQ(color.GetGreen(), sdlColor.g);
  EXPECT_EQ(color.GetBlue(), sdlColor.b);
  EXPECT_EQ(color.GetAlpha(), sdlColor.a);
}