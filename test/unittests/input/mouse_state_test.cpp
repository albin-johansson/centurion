#include "mouse_state.hpp"

#include <gtest/gtest.h>

#include <type_traits>

static_assert(std::is_final_v<cen::mouse_state>);

static_assert(std::is_nothrow_move_constructible_v<cen::mouse_state>);
static_assert(std::is_nothrow_move_assignable_v<cen::mouse_state>);

static_assert(std::is_nothrow_copy_constructible_v<cen::mouse_state>);
static_assert(std::is_nothrow_copy_assignable_v<cen::mouse_state>);

TEST(MouseState, Defaults)
{
  const cen::mouse_state state;
  EXPECT_EQ(1, state.logical_width());
  EXPECT_EQ(1, state.logical_height());

  EXPECT_EQ(0, state.mouse_x());
  EXPECT_EQ(0, state.mouse_y());

  EXPECT_EQ(cen::ipoint{}, state.mouse_pos());
}

TEST(MouseState, Update)
{
  cen::mouse_state state;
  EXPECT_NO_THROW(state.update({12, 632}));
}

TEST(MouseState, Reset)
{
  cen::mouse_state state;

  state.set_logical_width(455);
  state.set_logical_height(183);

  state.reset();

  EXPECT_EQ(1, state.logical_width());
  EXPECT_EQ(1, state.logical_height());
}

TEST(MouseState, SetLogicalWidth)
{
  cen::mouse_state state;

  const auto width = 821;
  state.set_logical_width(width);

  EXPECT_EQ(width, state.logical_width());
}

TEST(MouseState, SetLogicalHeight)
{
  cen::mouse_state state;

  const auto height = 219;
  state.set_logical_height(height);

  EXPECT_EQ(height, state.logical_height());
}

TEST(MouseState, SetLogicalSize)
{
  cen::mouse_state state;
  const cen::iarea size{823, 569};

  state.set_logical_size(size);
  EXPECT_EQ(size, state.logical_size());
}

TEST(MouseState, LogicalSize)
{
  cen::mouse_state state;

  const auto width = 342;
  const auto height = 219;

  state.set_logical_width(width);
  state.set_logical_height(height);

  const auto [actualWidth, actualHeight] = state.logical_size();
  EXPECT_EQ(width, actualWidth);
  EXPECT_EQ(height, actualHeight);
}

TEST(MouseState, IsLeftButtonPressed)
{
  const cen::mouse_state state;
  EXPECT_FALSE(state.is_left_button_pressed());
}

TEST(MouseState, IsRightButtonPressed)
{
  const cen::mouse_state state;
  EXPECT_FALSE(state.is_right_button_pressed());
}

TEST(MouseState, WasLeftButtonReleased)
{
  const cen::mouse_state state;
  EXPECT_FALSE(state.was_left_button_released());
}

TEST(MouseState, WasRightButtonReleased)
{
  const cen::mouse_state state;
  EXPECT_FALSE(state.was_right_button_released());
}

TEST(MouseState, WasMouseMoved)
{
  const cen::mouse_state state;
  EXPECT_FALSE(state.was_mouse_moved());
}
