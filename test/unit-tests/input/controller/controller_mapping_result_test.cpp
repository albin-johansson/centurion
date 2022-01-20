#include <gtest/gtest.h>

#include <iostream>  // cout

#include "controller.hpp"

using mapping_result = cen::controller_mapping_result;

TEST(ControllerMappingResult, ToString)
{
  ASSERT_THROW(to_string(static_cast<mapping_result>(4)), cen::exception);

  ASSERT_EQ("error", to_string(mapping_result::error));
  ASSERT_EQ("updated", to_string(mapping_result::updated));
  ASSERT_EQ("added", to_string(mapping_result::added));

  std::cout << "controller_mapping_result::added == " << mapping_result::added << '\n';
}
