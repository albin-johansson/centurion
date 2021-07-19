#include "audio/fade_status.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(FadeStatus, Values)
{
  ASSERT_EQ(cen::fade_status::none, MIX_NO_FADING);
  ASSERT_EQ(cen::fade_status::in, MIX_FADING_IN);
  ASSERT_EQ(cen::fade_status::out, MIX_FADING_OUT);

  ASSERT_EQ(MIX_NO_FADING, cen::fade_status::none);
  ASSERT_EQ(MIX_FADING_IN, cen::fade_status::in);
  ASSERT_EQ(MIX_FADING_OUT, cen::fade_status::out);

  ASSERT_NE(cen::fade_status::in, MIX_FADING_OUT);
  ASSERT_NE(MIX_FADING_OUT, cen::fade_status::none);
}

TEST(FadeStatus, ToString)
{
  ASSERT_EQ("none", cen::to_string(cen::fade_status::none));
  ASSERT_EQ("in", cen::to_string(cen::fade_status::in));
  ASSERT_EQ("out", cen::to_string(cen::fade_status::out));

  std::cout << "Fade status example: " << cen::fade_status::in << '\n';
}
