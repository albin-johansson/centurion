#include "centurion/mouse.hpp"

#include <gtest/gtest.h>

#include <iostream>     // cout
#include <type_traits>  // ...

static_assert(std::is_final_v<cen::mouse>);

static_assert(std::is_nothrow_move_constructible_v<cen::mouse>);
static_assert(std::is_nothrow_move_assignable_v<cen::mouse>);

static_assert(std::is_nothrow_copy_constructible_v<cen::mouse>);
static_assert(std::is_nothrow_copy_assignable_v<cen::mouse>);

TEST(Mouse, Defaults)
{
  const cen::mouse mouse;

  ASSERT_EQ(0, mouse.x());
  ASSERT_EQ(0, mouse.y());

  ASSERT_FALSE(mouse.is_left_pressed());
  ASSERT_FALSE(mouse.is_middle_pressed());
  ASSERT_FALSE(mouse.is_right_pressed());

  ASSERT_FALSE(mouse.was_left_released());
  ASSERT_FALSE(mouse.was_middle_released());
  ASSERT_FALSE(mouse.was_right_released());

  ASSERT_FALSE(mouse.was_moved());
}

TEST(Mouse, Update)
{
  cen::mouse mouse;
  ASSERT_NO_THROW(mouse.update());
}

TEST(Mouse, ToString)
{
  const cen::mouse mouse;
  ASSERT_EQ("mouse(x: 0, y: 0)", cen::to_string(mouse));

  std::cout << mouse << '\n';
}