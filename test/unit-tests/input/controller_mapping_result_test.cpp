#include <gtest/gtest.h>

#include <iostream>  // clog

#include "input/controller.hpp"

TEST(ControllerMappingResult, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::ControllerMappingResult>(4)), cen::Error);

  ASSERT_EQ("Error", cen::to_string(cen::ControllerMappingResult::Error));
  ASSERT_EQ("Updated", cen::to_string(cen::ControllerMappingResult::Updated));
  ASSERT_EQ("Added", cen::to_string(cen::ControllerMappingResult::Added));

  std::clog << "Controller mapping result example: " << cen::ControllerMappingResult::Added
            << '\n';
}
