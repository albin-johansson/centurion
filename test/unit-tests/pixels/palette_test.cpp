#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/logging.hpp"
#include "pixels.hpp"
#include "video/colors.hpp"

TEST(Palette, Constructor)
{
  ASSERT_THROW(cen::palette{0}, cen::Error);
  ASSERT_THROW(cen::palette{-1}, cen::Error);
  ASSERT_NO_THROW(cen::palette{1});
}

TEST(Palette, SetColor)
{
  cen::palette palette{4};

  ASSERT_TRUE(palette.set_color(0, cen::colors::coral));
  ASSERT_EQ(cen::colors::coral, palette.at(0));
  ASSERT_EQ(cen::colors::coral, palette[0]);

  ASSERT_TRUE(palette.set_color(1, cen::colors::cyan));
  ASSERT_EQ(cen::colors::cyan, palette.at(1));
  ASSERT_EQ(cen::colors::cyan, palette[1]);

  ASSERT_TRUE(palette.set_color(2, cen::colors::magenta));
  ASSERT_EQ(cen::colors::magenta, palette.at(2));
  ASSERT_EQ(cen::colors::magenta, palette[2]);

  ASSERT_TRUE(palette.set_color(3, cen::colors::red));
  ASSERT_EQ(cen::colors::red, palette.at(3));
  ASSERT_EQ(cen::colors::red, palette[3]);
}

TEST(Palette, Iteration)
{
  {
    cen::palette single{1};
    const auto count = single.end() - single.begin();

    ASSERT_EQ(1, count);
  }

  {
    cen::palette palette{4};
    const auto count = palette.end() - palette.begin();

    ASSERT_EQ(4, count);
  }
}

TEST(Palette, At)
{
  cen::palette palette{4};
  ASSERT_NO_THROW(palette.at(0));
  ASSERT_NO_THROW(palette.at(3));
  ASSERT_THROW(palette.at(-1), cen::Error);
  ASSERT_THROW(palette.at(4), cen::Error);
}

TEST(Palette, Size)
{
  const cen::palette palette{7};
  ASSERT_EQ(7, palette.size());
}

TEST(Palette, ToString)
{
  const cen::palette palette{7};
  cen::log_info_raw(cen::to_string(palette));
}

TEST(Palette, StreamOperator)
{
  const cen::palette palette{7};
  std::clog << palette << '\n';
}