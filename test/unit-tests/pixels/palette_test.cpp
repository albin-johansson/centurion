#include <gtest/gtest.h>

#include <iostream>  // clog

#include "color.hpp"
#include "core/logging.hpp"
#include "pixels.hpp"

TEST(Palette, Constructor)
{
  ASSERT_THROW(cen::Palette{0}, cen::exception);
  ASSERT_THROW(cen::Palette{-1}, cen::exception);
  ASSERT_NO_THROW(cen::Palette{1});
}

TEST(Palette, SetColor)
{
  cen::Palette palette{4};

  ASSERT_TRUE(palette.SetColor(0, cen::colors::coral));
  ASSERT_EQ(cen::colors::coral, palette.GetColor(0));

  ASSERT_TRUE(palette.SetColor(1, cen::colors::cyan));
  ASSERT_EQ(cen::colors::cyan, palette.GetColor(1));

  ASSERT_TRUE(palette.SetColor(2, cen::colors::magenta));
  ASSERT_EQ(cen::colors::magenta, palette.GetColor(2));

  ASSERT_TRUE(palette.SetColor(3, cen::colors::red));
  ASSERT_EQ(cen::colors::red, palette.GetColor(3));
}

TEST(Palette, Iteration)
{
  {
    cen::Palette single{1};
    const auto count = single.end() - single.begin();

    ASSERT_EQ(1, count);
  }

  {
    cen::Palette palette{4};
    const auto count = palette.end() - palette.begin();

    ASSERT_EQ(4, count);
  }
}

TEST(Palette, GetColor)
{
  cen::Palette palette{4};
  ASSERT_NO_THROW(palette.GetColor(0));
  ASSERT_NO_THROW(palette.GetColor(3));
  ASSERT_THROW(palette.GetColor(-1), cen::exception);
  ASSERT_THROW(palette.GetColor(4), cen::exception);
}

TEST(Palette, GetSize)
{
  const cen::Palette palette{7};
  ASSERT_EQ(7, palette.GetSize());
}

TEST(Palette, ToString)
{
  const cen::Palette palette{7};
  cen::log_info_raw(cen::ToString(palette));
}

TEST(Palette, StreamOperator)
{
  const cen::Palette palette{7};
  std::clog << palette << '\n';
}