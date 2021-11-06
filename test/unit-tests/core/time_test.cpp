#include "core/time.hpp"

#include <gtest/gtest.h>

TEST(Time, LegacyAliases)
{
  using namespace cen::literals::legacy;
  ASSERT_EQ(cen::u32_ns{123}, 123_ns);
  ASSERT_EQ(cen::u32_us{42}, 42_us);
  ASSERT_EQ(cen::u32_ms{185}, 185_ms);
  ASSERT_EQ(cen::u32_s{7}, 7_s);
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST(Time, Aliases)
{
  using namespace cen::literals;
  ASSERT_EQ(cen::u64_ns{123}, 123_ns);
  ASSERT_EQ(cen::u64_us{42}, 42_us);
  ASSERT_EQ(cen::u64_ms{185}, 185_ms);
  ASSERT_EQ(cen::u64_s{7}, 7_s);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)
