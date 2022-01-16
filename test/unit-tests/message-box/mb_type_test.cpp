#include <gtest/gtest.h>

#include <iostream>  // clog

#include "message_box.hpp"

TEST(MessageBoxType, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_INFORMATION, cen::to_underlying(cen::MessageBoxType::Information));
  ASSERT_EQ(SDL_MESSAGEBOX_WARNING, cen::to_underlying(cen::MessageBoxType::Warning));
  ASSERT_EQ(SDL_MESSAGEBOX_ERROR, cen::to_underlying(cen::MessageBoxType::Error));
}

TEST(MessageBoxType, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::MessageBoxType>(0x41)), cen::exception);

  ASSERT_EQ("Information", cen::ToString(cen::MessageBoxType::Information));
  ASSERT_EQ("Error", cen::ToString(cen::MessageBoxType::Error));
  ASSERT_EQ("Warning", cen::ToString(cen::MessageBoxType::Warning));

  std::clog << "Message box type example: " << cen::MessageBoxType::Information << '\n';
}
