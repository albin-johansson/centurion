// Copyright (C) 2019-2023 Albin Johansson (MIT License)

#include "centurion/detail/scope_exit.hpp"

#include <utility>

#include <gtest/gtest.h>

namespace cen::test {

// cen::detail::scope_exit<T>::~scope_exit
TEST(ScopeExit, Destructor)
{
  int value = 0;

  {
    value = 1;
    const detail::scope_exit guard
        [[maybe_unused]] {[&]() noexcept { value = 2; }};
    EXPECT_EQ(value, 1);
  }

  EXPECT_EQ(value, 2);
}

// cen::detail::scope_exit<T>::scope_exit(scope_exit&&)
TEST(ScopeExit, MoveConstructor)
{
  int value = 0;

  {
    detail::scope_exit guard1 {[&]() noexcept { ++value; }};
    const detail::scope_exit guard2 [[maybe_unused]] {std::move(guard1)};
  }

  EXPECT_EQ(value, 1);
}

}  // namespace cen::test
