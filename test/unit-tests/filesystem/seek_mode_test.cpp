#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "filesystem/file.hpp"

TEST(SeekMode, Values)
{
  ASSERT_EQ(RW_SEEK_SET, cen::ToUnderlying(cen::SeekMode::FromBeginning));
  ASSERT_EQ(RW_SEEK_CUR, cen::ToUnderlying(cen::SeekMode::RelativeToCurrent));
  ASSERT_EQ(RW_SEEK_END, cen::ToUnderlying(cen::SeekMode::RelativeToEnd));
}
