#include <gtest/gtest.h>

#include <iostream>  // clog

#include "input/controller.hpp"

TEST(ControllerMappingResult, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::controller::mapping_result>(4)),
               cen::Error);
  ASSERT_THROW(cen::to_string(static_cast<cen::controller_handle::mapping_result>(4)),
               cen::Error);

  ASSERT_EQ("error", cen::to_string(cen::controller::mapping_result::error));
  ASSERT_EQ("error", cen::to_string(cen::controller_handle::mapping_result::error));

  ASSERT_EQ("updated", cen::to_string(cen::controller::mapping_result::updated));
  ASSERT_EQ("updated", cen::to_string(cen::controller_handle::mapping_result::updated));

  ASSERT_EQ("added", cen::to_string(cen::controller::mapping_result::added));
  ASSERT_EQ("added", cen::to_string(cen::controller_handle::mapping_result::added));

  std::clog << "Controller mapping result example #1: "
            << cen::controller::mapping_result::added << '\n';

  std::clog << "Controller mapping result example #2: "
            << cen::controller_handle::mapping_result::added << '\n';
}
