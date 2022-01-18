#include <gtest/gtest.h>

#include <iostream>  // cout

#include "common.hpp"
#include "video.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 16)

TEST(FlashOp, Values)
{
  ASSERT_EQ(SDL_FLASH_CANCEL, to_underlying(cen::flash_op::cancel));
  ASSERT_EQ(SDL_FLASH_BRIEFLY, to_underlying(cen::flash_op::briefly));
  ASSERT_EQ(SDL_FLASH_UNTIL_FOCUSED, to_underlying(cen::flash_op::until_focused));
}

TEST(FlashOp, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::flash_op>(42)), cen::exception);

  ASSERT_EQ("cancel", to_string(cen::flash_op::cancel));
  ASSERT_EQ("briefly", to_string(cen::flash_op::briefly));
  ASSERT_EQ("until_focused", to_string(cen::flash_op::until_focused));

  std::cout << "flash_op::briefly == " << cen::flash_op::briefly << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)