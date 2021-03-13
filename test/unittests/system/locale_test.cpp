#include "locale.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(Locale, GetPreferred)
{
  // We assume that the systems that run these tests have English as an
  // available locale
  if (auto locale = cen::locale::get_preferred()) {
    EXPECT_LT(0, locale.count());
    EXPECT_TRUE(locale.has_language("en"));
    EXPECT_FALSE(locale.has_language("se"));
    EXPECT_FALSE(locale.has_language("foo", "bar"));
  } else {
    std::cout << "Could not obtain preferred locale!\n";
  }
}
