#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "filesystem.hpp"

TEST(SeekMode, Values)
{
  ASSERT_EQ(RW_SEEK_SET, cen::to_underlying(cen::SeekMode::FromBeginning));
  ASSERT_EQ(RW_SEEK_CUR, cen::to_underlying(cen::SeekMode::RelativeToCurrent));
  ASSERT_EQ(RW_SEEK_END, cen::to_underlying(cen::SeekMode::RelativeToEnd));
}
