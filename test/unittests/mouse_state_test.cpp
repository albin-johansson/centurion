#include "mouse_state.hpp"

#include <catch.hpp>

TEST_CASE("mouse_state()", "[mouse_state]")
{
  const cen::mouse_state state;
  CHECK(state.logical_width() == 1);
  CHECK(state.logical_height() == 1);
  CHECK(state.mouse_x() == 0);
  CHECK(state.mouse_y() == 0);
  CHECK(state.mouse_pos() == cen::ipoint{0, 0});
}

TEST_CASE("mouse_state::update", "[mouse_state]")
{
  cen::mouse_state state;

  CHECK_NOTHROW(state.update(12, 632));

  state.set_logical_width(234);
  state.set_logical_height(35);

  CHECK_NOTHROW(state.update());
}

TEST_CASE("mouse_state::reset", "[mouse_state]")
{
  cen::mouse_state state;

  state.set_logical_width(455);
  state.set_logical_height(183);

  state.reset();

  CHECK(state.logical_width() == 1);
  CHECK(state.logical_height() == 1);
}

TEST_CASE("mouse_state::set_logical_width", "[mouse_state]")
{
  cen::mouse_state state;

  const auto width = 821;
  state.set_logical_width(width);

  CHECK(width == state.logical_width());
}

TEST_CASE("mouse_state::set_logical_height", "[mouse_state]")
{
  cen::mouse_state state;

  const auto height = 219;
  state.set_logical_height(height);

  CHECK(height == state.logical_height());
}

TEST_CASE("mouse_state::is_left_button_pressed", "[mouse_state]")
{
  cen::mouse_state state;
  CHECK(!state.is_left_button_pressed());
}

TEST_CASE("mouse_state::is_right_button_pressed", "[mouse_state]")
{
  cen::mouse_state state;
  CHECK(!state.is_right_button_pressed());
}

TEST_CASE("mouse_state::was_left_button_released", "[mouse_state]")
{
  cen::mouse_state state;
  CHECK(!state.was_left_button_released());
}

TEST_CASE("mouse_state::was_right_button_released", "[mouse_state]")
{
  cen::mouse_state state;
  CHECK(!state.was_right_button_released());
}

TEST_CASE("mouse_state::was_mouse_moved", "[mouse_state]")
{
  cen::mouse_state state;
  CHECK(!state.was_mouse_moved());
}