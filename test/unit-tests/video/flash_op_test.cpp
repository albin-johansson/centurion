#include <gtest/gtest.h>

#include <iostream>  // cout

#include "common.hpp"
#include "video.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 16)

TEST(FlashOp, Values)
{
  ASSERT_EQ(SDL_FLASH_CANCEL, cen::ToUnderlying(cen::FlashOp::Cancel));
  ASSERT_EQ(SDL_FLASH_BRIEFLY, cen::ToUnderlying(cen::FlashOp::Briefly));
  ASSERT_EQ(SDL_FLASH_UNTIL_FOCUSED, cen::ToUnderlying(cen::FlashOp::UntilFocused));
}

TEST(FlashOp, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::FlashOp>(42)), cen::exception);

  ASSERT_EQ("Cancel", cen::ToString(cen::FlashOp::Cancel));
  ASSERT_EQ("Briefly", cen::ToString(cen::FlashOp::Briefly));
  ASSERT_EQ("UntilFocused", cen::ToString(cen::FlashOp::UntilFocused));

  std::cout << "Flash operation example: " << cen::FlashOp::Briefly << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)