#include "system/locale.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(Locale, GetPreferred)
{
  // We assume that the systems that run these tests have English as an
  // available locale
  if (auto locale = cen::locale::get_preferred()) {
    ASSERT_LT(0, locale.count());
    ASSERT_TRUE(locale.has_language("en"));
    ASSERT_FALSE(locale.has_language("se"));
    ASSERT_FALSE(locale.has_language("foo", "bar"));
  }
  else {
    std::clog << "Could not obtain preferred locale!\n";
  }
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)