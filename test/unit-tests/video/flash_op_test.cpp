#include "video/flash_op.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 16)

TEST(FlashOp, Values)
{
  ASSERT_EQ(SDL_FLASH_CANCEL, cen::to_underlying(cen::flash_op::cancel));
  ASSERT_EQ(SDL_FLASH_BRIEFLY, cen::to_underlying(cen::flash_op::briefly));
  ASSERT_EQ(SDL_FLASH_UNTIL_FOCUSED, cen::to_underlying(cen::flash_op::until_focused));
}

TEST(FlashOp, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::flash_op>(42)), cen::cen_error);

  ASSERT_EQ("cancel", cen::to_string(cen::flash_op::cancel));
  ASSERT_EQ("briefly", cen::to_string(cen::flash_op::briefly));
  ASSERT_EQ("until_focused", cen::to_string(cen::flash_op::until_focused));

  std::cout << "Flash operation example: " << cen::flash_op::briefly << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)