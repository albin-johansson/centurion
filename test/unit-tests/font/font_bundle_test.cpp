#include <gtest/gtest.h>

#include "font.hpp"

TEST(FontBundle, Usage)
{
  cen::FontBundle bundle;

  const auto a = bundle.LoadFont("resources/daniel.ttf", 12);
  ASSERT_EQ(1, bundle.GetNumUniqueFonts());
  ASSERT_EQ(1, bundle.GetNumFonts());

  const auto b = bundle.LoadFont("resources/daniel.ttf", 16);
  ASSERT_EQ(1, bundle.GetNumUniqueFonts());
  ASSERT_EQ(2, bundle.GetNumFonts());

  ASSERT_EQ(a, b);
  ASSERT_TRUE(bundle.HasFont("resources/daniel.ttf"));
  ASSERT_TRUE(bundle.HasFont(a));

  ASSERT_FALSE(bundle.HasFont(a, 11));
  ASSERT_TRUE(bundle.HasFont(a, 12));
  ASSERT_FALSE(bundle.HasFont(a, 13));

  ASSERT_FALSE(bundle.HasFont(a, 15));
  ASSERT_TRUE(bundle.HasFont(a, 16));
  ASSERT_FALSE(bundle.HasFont(a, 17));

  const auto c = bundle.LoadFont("resources/type_writer.ttf", 9);
  ASSERT_EQ(2, bundle.GetNumUniqueFonts());
  ASSERT_EQ(3, bundle.GetNumFonts());

  ASSERT_NE(a, c);
  ASSERT_TRUE(bundle.HasFont(c));
  ASSERT_TRUE(bundle.HasFont("resources/type_writer.ttf"));

  ASSERT_STREQ("Daniel", bundle.GetFont(a, 12).GetFamilyName());
  ASSERT_ANY_THROW(bundle.GetFont(a, 11));
  ASSERT_ANY_THROW(bundle.GetFont(a, 13));

  ASSERT_STREQ("Type Writer", bundle.GetFont(c, 9).GetFamilyName());
  ASSERT_ANY_THROW(bundle.GetFont(c, 8));
  ASSERT_ANY_THROW(bundle.GetFont(c, 10));
}