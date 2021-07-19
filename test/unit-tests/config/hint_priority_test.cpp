#include "hints/hint_priority.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"

TEST(HintPriority, Values)
{
  ASSERT_EQ(SDL_HINT_DEFAULT, cen::to_underlying(cen::hint_priority::low));
  ASSERT_EQ(SDL_HINT_NORMAL, cen::to_underlying(cen::hint_priority::normal));
  ASSERT_EQ(SDL_HINT_OVERRIDE, cen::to_underlying(cen::hint_priority::override));
}

TEST(HintPriority, ToString)
{
  ASSERT_EQ("low", cen::to_string(cen::hint_priority::low));
  ASSERT_EQ("normal", cen::to_string(cen::hint_priority::normal));
  ASSERT_EQ("override", cen::to_string(cen::hint_priority::override));

  std::cout << "Hint priority example: " << cen::hint_priority::override << '\n';
}
