#include "mouse_state.hpp"

#include <catch.hpp>

using namespace centurion;
using namespace centurion::input;

TEST_CASE("MouseState()", "[MouseState]")
{
  const MouseState state;
  CHECK(state.logical_width() == 1);
  CHECK(state.logical_height() == 1);
  CHECK(state.mouse_x() == 0);
  CHECK(state.mouse_y() == 0);
}

TEST_CASE("MouseState smart pointer factory methods", "[MouseState]")
{
  CHECK(MouseState::unique());
  CHECK(MouseState::shared());
}

TEST_CASE("MouseState::update", "[MouseState]")
{
  MouseState state;

  CHECK_NOTHROW(state.update(12, 632));

  state.set_logical_width(234);
  state.set_logical_height(35);

  CHECK_NOTHROW(state.update());
}

TEST_CASE("MouseState::reset", "[MouseState]")
{
  MouseState state;

  state.set_logical_width(455);
  state.set_logical_height(183);

  state.reset();

  CHECK(state.logical_width() == 1);
  CHECK(state.logical_height() == 1);
}

TEST_CASE("MouseState::set_logical_width", "[MouseState]")
{
  MouseState state;

  const auto width = 821;
  state.set_logical_width(width);

  CHECK(width == state.logical_width());
}

TEST_CASE("MouseState::set_logical_height", "[MouseState]")
{
  MouseState state;

  const auto height = 219;
  state.set_logical_height(height);

  CHECK(height == state.logical_height());
}

TEST_CASE("MouseState::is_left_button_pressed", "[MouseState]")
{
  MouseState state;
  CHECK(!state.is_left_button_pressed());
}

TEST_CASE("MouseState::is_right_button_pressed", "[MouseState]")
{
  MouseState state;
  CHECK(!state.is_right_button_pressed());
}

TEST_CASE("MouseState::was_left_button_released", "[MouseState]")
{
  MouseState state;
  CHECK(!state.was_left_button_released());
}

TEST_CASE("MouseState::was_right_button_released", "[MouseState]")
{
  MouseState state;
  CHECK(!state.was_right_button_released());
}

TEST_CASE("MouseState::was_mouse_moved", "[MouseState]")
{
  MouseState state;
  CHECK(!state.was_mouse_moved());
}