#include <gtest/gtest.h>

#include <iostream>  // cout

#include "audio.hpp"
#include "common.hpp"

TEST(FadeStatus, Values)
{
  ASSERT_EQ(MIX_NO_FADING, to_underlying(cen::fade_status::none));
  ASSERT_EQ(MIX_FADING_IN, to_underlying(cen::fade_status::in));
  ASSERT_EQ(MIX_FADING_OUT, to_underlying(cen::fade_status::out));
}

TEST(FadeStatus, ToString)
{
  ASSERT_EQ("none", to_string(cen::fade_status::none));
  ASSERT_EQ("in", to_string(cen::fade_status::in));
  ASSERT_EQ("out", to_string(cen::fade_status::out));

  std::cout << "fade_status::in == " << cen::fade_status::in << '\n';
}
