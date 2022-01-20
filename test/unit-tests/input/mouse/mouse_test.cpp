#include "mouse.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <type_traits>

static_assert(std::is_final_v<cen::Mouse>);

static_assert(std::is_nothrow_move_constructible_v<cen::Mouse>);
static_assert(std::is_nothrow_move_assignable_v<cen::Mouse>);

static_assert(std::is_nothrow_copy_constructible_v<cen::Mouse>);
static_assert(std::is_nothrow_copy_assignable_v<cen::Mouse>);

TEST(Mouse, Defaults)
{
  const cen::Mouse mouse;

  ASSERT_EQ(0, mouse.x());
  ASSERT_EQ(0, mouse.y());

  ASSERT_EQ(1, mouse.GetLogicalWidth());
  ASSERT_EQ(1, mouse.GetLogicalHeight());

  ASSERT_FALSE(mouse.IsLeftButtonPressed());
  ASSERT_FALSE(mouse.IsMiddleButtonPressed());
  ASSERT_FALSE(mouse.IsRightButtonPressed());

  ASSERT_FALSE(mouse.WasLeftButtonReleased());
  ASSERT_FALSE(mouse.WasMiddleButtonReleased());
  ASSERT_FALSE(mouse.WasRightButtonReleased());

  ASSERT_FALSE(mouse.WasMoved());
}

TEST(Mouse, Update)
{
  cen::Mouse mouse;
  ASSERT_NO_THROW(mouse.Update({12, 632}));
}

TEST(Mouse, ResetLogicalSize)
{
  cen::Mouse mouse;

  const cen::farea size{455, 183};
  mouse.SetLogicalSize(size);

  mouse.ResetLogicalSize();
  ASSERT_EQ(1, mouse.GetLogicalWidth());
  ASSERT_EQ(1, mouse.GetLogicalHeight());
}

TEST(Mouse, SetLogicalSize)
{
  cen::Mouse mouse;

  const cen::farea size{821, 219};
  mouse.SetLogicalSize(size);

  ASSERT_EQ(size.width, mouse.GetLogicalSize().width);
  ASSERT_EQ(size.height, mouse.GetLogicalSize().height);
}

TEST(Mouse, ToString)
{
  const cen::Mouse mouse;
  ASSERT_EQ("Mouse(x: 0, y: 0)", cen::ToString(mouse));

  std::clog << mouse << '\n';
}