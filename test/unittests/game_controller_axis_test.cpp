#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "game_controller.hpp"

TEST_CASE("gamecontroller::axis operator==", "[gamecontroller::axis]")
{
  CHECK(SDL_CONTROLLER_AXIS_INVALID == ctn::gamepad_axis::invalid);
  CHECK(SDL_CONTROLLER_AXIS_LEFTX == ctn::gamepad_axis::left_x);
  CHECK(SDL_CONTROLLER_AXIS_LEFTY == ctn::gamepad_axis::left_y);
  CHECK(SDL_CONTROLLER_AXIS_RIGHTX == ctn::gamepad_axis::right_x);
  CHECK(SDL_CONTROLLER_AXIS_RIGHTY == ctn::gamepad_axis::right_y);
  CHECK(SDL_CONTROLLER_AXIS_TRIGGERLEFT == ctn::gamepad_axis::trigger_left);
  CHECK(SDL_CONTROLLER_AXIS_TRIGGERRIGHT == ctn::gamepad_axis::trigger_right);
  CHECK(SDL_CONTROLLER_AXIS_MAX == ctn::gamepad_axis::max);

  CHECK(ctn::gamepad_axis::invalid == SDL_CONTROLLER_AXIS_INVALID);
  CHECK(ctn::gamepad_axis::left_x == SDL_CONTROLLER_AXIS_LEFTX);
  CHECK(ctn::gamepad_axis::left_y == SDL_CONTROLLER_AXIS_LEFTY);
  CHECK(ctn::gamepad_axis::right_x == SDL_CONTROLLER_AXIS_RIGHTX);
  CHECK(ctn::gamepad_axis::right_y == SDL_CONTROLLER_AXIS_RIGHTY);
  CHECK(ctn::gamepad_axis::trigger_left == SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  CHECK(ctn::gamepad_axis::trigger_right == SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  CHECK(ctn::gamepad_axis::max == SDL_CONTROLLER_AXIS_MAX);
}

TEST_CASE("gamecontroller::axis operator!=", "[gamecontroller::axis]")
{
  CHECK(SDL_CONTROLLER_AXIS_INVALID != ctn::gamepad_axis::right_x);
  CHECK(ctn::gamepad_axis::max != SDL_CONTROLLER_AXIS_LEFTX);

  CHECK(
      !(SDL_CONTROLLER_AXIS_TRIGGERRIGHT != ctn::gamepad_axis::trigger_right));
}
