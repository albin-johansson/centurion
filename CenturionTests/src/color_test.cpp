#include <pch.h>

TEST(ColorTest, ctor) {
  int overflow = Color::MAX_VAL + 11294;

  EXPECT_NO_THROW(Color(overflow, 0, 0, 0));
  EXPECT_NO_THROW(Color(0, overflow, 0, 0));
  EXPECT_NO_THROW(Color(0, 0, overflow, 0));
  EXPECT_NO_THROW(Color(0, 0, 0, overflow));
}

static bool Equal(Color a, Color b) {
  return (a.GetRed() == b.GetRed()) && (a.GetGreen() == b.GetGreen()) &&
         (a.GetBlue() == b.GetBlue()) && (a.GetAlpha() == b.GetAlpha());
}

TEST(ColorTest, constants) {
  EXPECT_EQ(Color::MAX_VAL, 0xFF);
  EXPECT_EQ(Color::MIN_VAL, 0);

  EXPECT_TRUE(Equal(Color::RED, Color(0xFF, 0, 0)));
  EXPECT_TRUE(Equal(Color::GREEN, Color(0, 0xFF, 0)));
  EXPECT_TRUE(Equal(Color::BLUE, Color(0, 0, 0xFF)));
  EXPECT_TRUE(Equal(Color::WHITE, Color(0xFF, 0xFF, 0xFF)));
  EXPECT_TRUE(Equal(Color::BLACK, Color(0, 0, 0)));
}

TEST(ColorTest, getters) {
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