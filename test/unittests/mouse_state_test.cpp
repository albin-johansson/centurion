#include "catch.hpp"
#include "mouse_state.h"

using namespace centurion;

TEST_CASE("MouseState()", "[MouseState]") {
  const MouseState state;
  CHECK(state.get_logical_width() == 1);
  CHECK(state.get_logical_height() == 1);
  CHECK(state.get_window_width() == 1);
  CHECK(state.get_window_height() == 1);
  CHECK(state.get_mouse_x() == 0);
  CHECK(state.get_mouse_y() == 0);
}

TEST_CASE("MouseState smart pointer factory methods", "[MouseState]") {
  CHECK(MouseState::unique());
  CHECK(MouseState::shared());
}

TEST_CASE("MouseState::reset", "[MouseState]") {
  MouseState state;

  state.set_window_height(912);
  state.set_window_height(124);
  state.set_logical_width(455);
  state.set_logical_height(183);

  state.reset();

  CHECK(state.get_window_width() == 1);
  CHECK(state.get_window_height() == 1);
  CHECK(state.get_logical_width() == 1);
  CHECK(state.get_logical_height() == 1);
}

TEST_CASE("MouseState::set_logical_width", "[MouseState]") {
  MouseState state;

  const auto width = 821;
  state.set_logical_width(width);

  CHECK(width == state.get_logical_width());
}

TEST_CASE("MouseState::set_logical_height", "[MouseState]") {
  MouseState state;

  const auto height = 219;
  state.set_logical_height(height);

  CHECK(height == state.get_logical_height());
}

TEST_CASE("MouseState::set_window_width", "[MouseState]") {
  MouseState state;

  const auto width = 771;
  state.set_window_width(width);

  CHECK(width == state.get_window_width());
}

TEST_CASE("MouseState::set_window_height", "[MouseState]") {
  MouseState state;

  const auto height = 373;
  state.set_window_height(height);

  CHECK(height == state.get_window_height());
}

TEST_CASE("MouseState::is_left_button_pressed", "[MouseState]") {
  MouseState state;
  CHECK(!state.is_left_button_pressed());
}

TEST_CASE("MouseState::is_right_button_pressed", "[MouseState]") {
  MouseState state;
  CHECK(!state.is_right_button_pressed());
}

TEST_CASE("MouseState::was_left_button_released", "[MouseState]") {
  MouseState state;
  CHECK(!state.was_left_button_released());
}

TEST_CASE("MouseState::was_right_button_released", "[MouseState]") {
  MouseState state;
  CHECK(!state.was_right_button_released());
}

TEST_CASE("MouseState::was_mouse_moved", "[MouseState]") {
  MouseState state;
  CHECK(!state.was_mouse_moved());
}