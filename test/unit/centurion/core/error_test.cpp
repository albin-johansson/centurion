// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/core/error.hpp"

#include <string_view>

#include <gtest/gtest.h>

namespace cen::test {
inline namespace error_test {

inline int _message_count = 0;

}  // namespace error_test

// cen::set_error_message_callback
// cen::emit_error_message
TEST(Error, SetErrorMessageCallback)
{
  const auto callback = [](std::string_view) noexcept { ++_message_count; };
  set_error_message_callback(callback);

  EXPECT_EQ(_message_count, 0);
  emit_error_message("1");
  emit_error_message("2");
  emit_error_message("3");
  EXPECT_EQ(_message_count, 3);

  reset_error_message_callback();
}

}  // namespace cen::test
