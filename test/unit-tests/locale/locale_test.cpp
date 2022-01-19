#include "locale.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(Locale, GetPreferred)
{
  // We assume that the systems that run these tests have English as an
  // available locale
  if (auto locale = cen::Locale::GetPreferred()) {
    ASSERT_LT(0, locale.GetSize());
    ASSERT_TRUE(locale.HasLanguage("en"));
    ASSERT_FALSE(locale.HasLanguage("se"));
    ASSERT_FALSE(locale.HasLanguage("foo", "bar"));
  }
  else {
    std::clog << "Could not obtain preferred locale!\n";
  }
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)