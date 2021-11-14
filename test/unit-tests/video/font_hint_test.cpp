#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "video/font.hpp"

TEST(FontHint, Values)
{
  ASSERT_EQ(TTF_HINTING_NORMAL, cen::to_underlying(cen::font_hint::normal));
  ASSERT_EQ(TTF_HINTING_LIGHT, cen::to_underlying(cen::font_hint::light));
  ASSERT_EQ(TTF_HINTING_MONO, cen::to_underlying(cen::font_hint::mono));
  ASSERT_EQ(TTF_HINTING_NONE, cen::to_underlying(cen::font_hint::none));
}

TEST(FontHint, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::font_hint>(4)), cen::cen_error);

  ASSERT_EQ("normal", cen::to_string(cen::font_hint::normal));
  ASSERT_EQ("light", cen::to_string(cen::font_hint::light));
  ASSERT_EQ("mono", cen::to_string(cen::font_hint::mono));
  ASSERT_EQ("none", cen::to_string(cen::font_hint::none));

  std::clog << "Font hint example: " << cen::font_hint::normal << '\n';
}
