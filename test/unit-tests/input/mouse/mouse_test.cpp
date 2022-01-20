#include "mouse.hpp"

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

  ASSERT_EQ(1, mouse.logical_width());
  ASSERT_EQ(1, mouse.logical_height());

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
  ASSERT_NO_THROW(mouse.update({12, 632}));
}

TEST(Mouse, ResetLogicalSize)
{
  cen::mouse mouse;

  const cen::farea size{455, 183};
  mouse.set_logical_size(size);

  mouse.reset_logical_size();
  ASSERT_EQ(1, mouse.logical_width());
  ASSERT_EQ(1, mouse.logical_height());
}

TEST(Mouse, SetLogicalSize)
{
  cen::mouse mouse;

  const cen::farea size{821, 219};
  mouse.set_logical_size(size);

  ASSERT_EQ(size.width, mouse.logical_width());
  ASSERT_EQ(size.height, mouse.logical_height());
}

TEST(Mouse, ToString)
{
  const cen::mouse mouse;
  ASSERT_EQ("mouse(x: 0, y: 0)", cen::to_string(mouse));

  std::cout << mouse << '\n';
}