#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "font.hpp"

TEST(FontHint, Values)
{
  ASSERT_EQ(TTF_HINTING_NORMAL, to_underlying(cen::font_hint::normal));
  ASSERT_EQ(TTF_HINTING_LIGHT, to_underlying(cen::font_hint::light));
  ASSERT_EQ(TTF_HINTING_MONO, to_underlying(cen::font_hint::mono));
  ASSERT_EQ(TTF_HINTING_NONE, to_underlying(cen::font_hint::none));
}

TEST(FontHint, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::font_hint>(4)), cen::exception);

  ASSERT_EQ("normal", to_string(cen::font_hint::normal));
  ASSERT_EQ("light", to_string(cen::font_hint::light));
  ASSERT_EQ("mono", to_string(cen::font_hint::mono));
  ASSERT_EQ("none", to_string(cen::font_hint::none));

  std::clog << "Font hint example: " << cen::font_hint::normal << '\n';
}
