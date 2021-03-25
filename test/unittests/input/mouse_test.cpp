#include "input/mouse.hpp"

#include <gtest/gtest.h>

#include <type_traits>

static_assert(std::is_final_v<cen::mouse>);

static_assert(std::is_nothrow_move_constructible_v<cen::mouse>);
static_assert(std::is_nothrow_move_assignable_v<cen::mouse>);

static_assert(std::is_nothrow_copy_constructible_v<cen::mouse>);
static_assert(std::is_nothrow_copy_assignable_v<cen::mouse>);

TEST(Mouse, Defaults)
{
  const cen::mouse mouse;
  EXPECT_EQ(1, mouse.logical_width());
  EXPECT_EQ(1, mouse.logical_height());

  EXPECT_EQ(0, mouse.x());
  EXPECT_EQ(0, mouse.y());

  EXPECT_EQ(cen::ipoint{}, mouse.position());
}

TEST(Mouse, Update)
{
  cen::mouse mouse;
  EXPECT_NO_THROW(mouse.update({12, 632}));
}

TEST(Mouse, Reset)
{
  cen::mouse mouse;

  mouse.set_logical_width(455);
  mouse.set_logical_height(183);

  mouse.reset();

  EXPECT_EQ(1, mouse.logical_width());
  EXPECT_EQ(1, mouse.logical_height());
}

TEST(Mouse, SetLogicalWidth)
{
  cen::mouse mouse;

  const auto width = 821;
  mouse.set_logical_width(width);

  EXPECT_EQ(width, mouse.logical_width());
}

TEST(Mouse, SetLogicalHeight)
{
  cen::mouse mouse;

  const auto height = 219;
  mouse.set_logical_height(height);

  EXPECT_EQ(height, mouse.logical_height());
}

TEST(Mouse, SetLogicalSize)
{
  cen::mouse mouse;
  const cen::iarea size{823, 569};

  mouse.set_logical_size(size);
  EXPECT_EQ(size, mouse.logical_size());
}

TEST(Mouse, LogicalSize)
{
  cen::mouse mouse;

  const auto width = 342;
  const auto height = 219;

  mouse.set_logical_width(width);
  mouse.set_logical_height(height);

  const auto [actualWidth, actualHeight] = mouse.logical_size();
  EXPECT_EQ(width, actualWidth);
  EXPECT_EQ(height, actualHeight);
}

TEST(Mouse, IsLeftButtonPressed)
{
  const cen::mouse mouse;
  EXPECT_FALSE(mouse.is_left_button_pressed());
}

TEST(Mouse, IsRightButtonPressed)
{
  const cen::mouse mouse;
  EXPECT_FALSE(mouse.is_right_button_pressed());
}

TEST(Mouse, WasLeftButtonReleased)
{
  const cen::mouse mouse;
  EXPECT_FALSE(mouse.was_left_button_released());
}

TEST(Mouse, WasRightButtonReleased)
{
  const cen::mouse mouse;
  EXPECT_FALSE(mouse.was_right_button_released());
}

TEST(Mouse, WasMoved)
{
  const cen::mouse mouse;
  EXPECT_FALSE(mouse.was_moved());
}
