#include <gtest/gtest.h>

#include <iostream>  // clog

#include "input/controller.hpp"

using MappingResult = cen::ControllerMappingResult;

TEST(ControllerMappingResult, ToString)
{
  ASSERT_THROW(to_string(static_cast<MappingResult>(4)), cen::Error);

  ASSERT_EQ("Error", to_string(MappingResult::Error));
  ASSERT_EQ("Updated", to_string(MappingResult::Updated));
  ASSERT_EQ("Added", to_string(MappingResult::Added));

  std::clog << "Controller mapping result example: " << MappingResult::Added << '\n';
}
