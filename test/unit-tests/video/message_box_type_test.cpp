#include "video/message_box_type.hpp"

#include <gtest/gtest.h>

#include "core/to_underlying.hpp"

TEST(MessageBoxType, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_INFORMATION,
            cen::to_underlying(cen::message_box_type::information));
  ASSERT_EQ(SDL_MESSAGEBOX_WARNING, cen::to_underlying(cen::message_box_type::warning));
  ASSERT_EQ(SDL_MESSAGEBOX_ERROR, cen::to_underlying(cen::message_box_type::error));
}
