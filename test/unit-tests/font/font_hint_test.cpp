#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "font.hpp"

TEST(FontHint, Values)
{
  ASSERT_EQ(TTF_HINTING_NORMAL, cen::ToUnderlying(cen::FontHint::Normal));
  ASSERT_EQ(TTF_HINTING_LIGHT, cen::ToUnderlying(cen::FontHint::Light));
  ASSERT_EQ(TTF_HINTING_MONO, cen::ToUnderlying(cen::FontHint::Mono));
  ASSERT_EQ(TTF_HINTING_NONE, cen::ToUnderlying(cen::FontHint::None));
}

TEST(FontHint, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::FontHint>(4)), cen::Error);

  ASSERT_EQ("Normal", cen::to_string(cen::FontHint::Normal));
  ASSERT_EQ("Light", cen::to_string(cen::FontHint::Light));
  ASSERT_EQ("Mono", cen::to_string(cen::FontHint::Mono));
  ASSERT_EQ("None", cen::to_string(cen::FontHint::None));

  std::clog << "Font hint example: " << cen::FontHint::Normal << '\n';
}
