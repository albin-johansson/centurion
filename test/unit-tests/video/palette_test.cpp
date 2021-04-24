#include "video/palette.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/log.hpp"
#include "video/colors.hpp"

TEST(Palette, Constructor)
{
  EXPECT_THROW(cen::palette{0}, cen::cen_error);
  EXPECT_THROW(cen::palette{-1}, cen::cen_error);
  EXPECT_NO_THROW(cen::palette{1});
}

TEST(Palette, SetColor)
{
  cen::palette palette{4};

  EXPECT_TRUE(palette.set_color(0, cen::colors::coral));
  EXPECT_EQ(cen::colors::coral, palette.at(0));
  EXPECT_EQ(cen::colors::coral, palette[0]);

  EXPECT_TRUE(palette.set_color(1, cen::colors::cyan));
  EXPECT_EQ(cen::colors::cyan, palette.at(1));
  EXPECT_EQ(cen::colors::cyan, palette[1]);

  EXPECT_TRUE(palette.set_color(2, cen::colors::magenta));
  EXPECT_EQ(cen::colors::magenta, palette.at(2));
  EXPECT_EQ(cen::colors::magenta, palette[2]);

  EXPECT_TRUE(palette.set_color(3, cen::colors::red));
  EXPECT_EQ(cen::colors::red, palette.at(3));
  EXPECT_EQ(cen::colors::red, palette[3]);
}

TEST(Palette, Iteration)
{
  {
    cen::palette single{1};

    auto count = 0;
    for (const auto& color : single)
    {
      ++count;
    }

    EXPECT_EQ(1, count);
  }

  {
    cen::palette palette{4};

    auto count = 0;
    for (const auto& color : palette)
    {
      ++count;
    }

    EXPECT_EQ(4, count);
  }
}

TEST(Palette, At)
{
  cen::palette palette{4};
  EXPECT_NO_THROW(palette.at(0));
  EXPECT_NO_THROW(palette.at(3));
  EXPECT_THROW(palette.at(-1), cen::cen_error);
  EXPECT_THROW(palette.at(4), cen::cen_error);
}

TEST(Palette, Size)
{
  const cen::palette palette{7};
  EXPECT_EQ(7, palette.size());
}

TEST(Palette, ToString)
{
  const cen::palette palette{7};
  cen::log::put(cen::to_string(palette));
}

TEST(Palette, StreamOperator)
{
  const cen::palette palette{7};
  std::cout << "COUT: " << palette << '\n';
}