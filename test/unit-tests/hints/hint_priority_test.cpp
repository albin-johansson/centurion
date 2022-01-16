#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
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

  //  ASSERT_THROW(cen::ToString(static_cast<cen::hint_priority>(4)), cen::exception);
  //
  //  ASSERT_EQ("low", cen::ToString(cen::hint_priority::low));
  //  ASSERT_EQ("normal", cen::ToString(cen::hint_priority::normal));
  //  ASSERT_EQ("override", cen::ToString(cen::hint_priority::override));
}
