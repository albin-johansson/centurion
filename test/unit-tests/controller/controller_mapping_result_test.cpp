#include <gtest/gtest.h>

#include <iostream>  // clog

#include "input/controller.hpp"

using MappingResult = cen::ControllerMappingResult;

TEST(ControllerMappingResult, ToString)
{
  ASSERT_THROW(ToString(static_cast<MappingResult>(4)), cen::Error);

  ASSERT_EQ("Error", ToString(MappingResult::Error));
  ASSERT_EQ("Updated", ToString(MappingResult::Updated));
  ASSERT_EQ("Added", ToString(MappingResult::Added));

  std::clog << "Controller mapping result example: " << MappingResult::Added << '\n';
}
