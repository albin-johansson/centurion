#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "core/hints.hpp"

TEST(HintPriority, Values)
{
  ASSERT_EQ(SDL_HINT_DEFAULT, cen::to_underlying(cen::hint_priority::low));
  ASSERT_EQ(SDL_HINT_NORMAL, cen::to_underlying(cen::hint_priority::normal));
  ASSERT_EQ(SDL_HINT_OVERRIDE, cen::to_underlying(cen::hint_priority::override));
}

TEST(HintPriority, ToString)
{
  // TODO

  //  ASSERT_THROW(cen::to_string(static_cast<cen::hint_priority>(4)), cen::cen_error);
  //
  //  ASSERT_EQ("low", cen::to_string(cen::hint_priority::low));
  //  ASSERT_EQ("normal", cen::to_string(cen::hint_priority::normal));
  //  ASSERT_EQ("override", cen::to_string(cen::hint_priority::override));
}
