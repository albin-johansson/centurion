#include <pch.h>

TEST(BoolConverter, conversion1) {
  bool t = BoolConverter::Convert(SDL_TRUE);
  EXPECT_TRUE(t);

  bool f = BoolConverter::Convert(SDL_FALSE);
  EXPECT_FALSE(f);
}

TEST(BoolConverter, conversion2) {
  SDL_bool t = BoolConverter::Convert(true);
  if (!t) {
    FAIL();
  }

  SDL_bool f = BoolConverter::Convert(false);
  if (f) {
    FAIL();
  }
}