#include "input/mouse.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <type_traits>

static_assert(std::is_final_v<cen::mouse>);

static_assert(std::is_nothrow_move_constructible_v<cen::mouse>);
static_assert(std::is_nothrow_move_assignable_v<cen::mouse>);

static_assert(std::is_nothrow_copy_constructible_v<cen::mouse>);
static_assert(std::is_nothrow_copy_assignable_v<cen::mouse>);

TEST(Mouse, Defaults)
{
  const cen::mouse mouse;
  ASSERT_EQ(1, mouse.logical_width());
  ASSERT_EQ(1, mouse.logical_height());

  ASSERT_EQ(0, mouse.x());
  ASSERT_EQ(0, mouse.y());

  ASSERT_EQ(cen::ipoint{}, mouse.position());
}

TEST(Mouse, Update)
{
  cen::mouse mouse;
  ASSERT_NO_THROW(mouse.update({12, 632}));
}

TEST(Mouse, Reset)
{
  cen::mouse mouse;

  mouse.set_logical_width(455);
  mouse.set_logical_height(183);

  mouse.reset();

  ASSERT_EQ(1, mouse.logical_width());
  ASSERT_EQ(1, mouse.logical_height());
}

TEST(Mouse, SetLogicalWidth)
{
  cen::mouse mouse;

  const auto width = 821;
  mouse.set_logical_width(width);

  ASSERT_EQ(width, mouse.logical_width());
}

TEST(Mouse, SetLogicalHeight)
{
  cen::mouse mouse;

  const auto height = 219;
  mouse.set_logical_height(height);

  ASSERT_EQ(height, mouse.logical_height());
}

TEST(Mouse, SetLogicalSize)
{
  cen::mouse mouse;
  const cen::iarea size{823, 569};

  mouse.set_logical_size(size);
  ASSERT_EQ(size, mouse.logical_size());
}

TEST(Mouse, LogicalSize)
{
  cen::mouse mouse;

  const auto width = 342;
  const auto height = 219;

  mouse.set_logical_width(width);
  mouse.set_logical_height(height);

  const auto [actualWidth, actualHeight] = mouse.logical_size();
  ASSERT_EQ(width, actualWidth);
  ASSERT_EQ(height, actualHeight);
}

TEST(Mouse, IsLeftButtonPressed)
{
  const cen::mouse mouse;
  ASSERT_FALSE(mouse.is_left_button_pressed());
}

TEST(Mouse, IsRightButtonPressed)
{
  const cen::mouse mouse;
  ASSERT_FALSE(mouse.is_right_button_pressed());
}

TEST(Mouse, WasLeftButtonReleased)
{
  const cen::mouse mouse;
  ASSERT_FALSE(mouse.was_left_button_released());
}

TEST(Mouse, WasRightButtonReleased)
{
  const cen::mouse mouse;
  ASSERT_FALSE(mouse.was_right_button_released());
}

TEST(Mouse, WasMoved)
{
  const cen::mouse mouse;
  ASSERT_FALSE(mouse.was_moved());
}

TEST(Mouse, ToString)
{
  const cen::mouse mouse;
  ASSERT_EQ("mouse{x: 0, y: 0}", cen::to_string(mouse));

  std::clog << mouse;
}