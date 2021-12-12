#include <gtest/gtest.h>

#include <iostream>  // clog

#include "audio/music.hpp"
#include "core/common.hpp"

TEST(FadeStatus, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::FadeStatus::None), MIX_NO_FADING);
  ASSERT_EQ(cen::to_underlying(cen::FadeStatus::In), MIX_FADING_IN);
  ASSERT_EQ(cen::to_underlying(cen::FadeStatus::Out), MIX_FADING_OUT);
}
