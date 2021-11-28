#include <gtest/gtest.h>

#include <iostream>  // clog

#include "audio.hpp"
#include "core/common.hpp"

TEST(FadeStatus, Values)
{
  ASSERT_EQ(3, cen::fade_status_count());

  ASSERT_EQ(cen::to_underlying(cen::fade_status::none), MIX_NO_FADING);
  ASSERT_EQ(cen::to_underlying(cen::fade_status::in), MIX_FADING_IN);
  ASSERT_EQ(cen::to_underlying(cen::fade_status::out), MIX_FADING_OUT);
}

TEST(FadeStatus, ToString)
{
  ASSERT_EQ("none", cen::to_string(cen::fade_status::none));
  ASSERT_EQ("in", cen::to_string(cen::fade_status::in));
  ASSERT_EQ("out", cen::to_string(cen::fade_status::out));

  std::clog << "Fade status example: " << cen::fade_status::in << '\n';
}
