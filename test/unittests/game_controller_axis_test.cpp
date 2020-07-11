#include <catch.hpp>

#include "game_controller.hpp"

using namespace centurion;

TEST_CASE("game_controller_axis operator==", "[game_controller_axis]")
{
  using gca = game_controller_axis;

  CHECK(SDL_CONTROLLER_AXIS_INVALID == gca::invalid);
  CHECK(SDL_CONTROLLER_AXIS_LEFTX == gca::left_x);
  CHECK(SDL_CONTROLLER_AXIS_LEFTY == gca::left_y);
  CHECK(SDL_CONTROLLER_AXIS_RIGHTX == gca::right_x);
  CHECK(SDL_CONTROLLER_AXIS_RIGHTY == gca::right_y);
  CHECK(SDL_CONTROLLER_AXIS_TRIGGERLEFT == gca::trigger_left);
  CHECK(SDL_CONTROLLER_AXIS_TRIGGERRIGHT == gca::trigger_right);
  CHECK(SDL_CONTROLLER_AXIS_MAX == gca::max);

  CHECK(gca::invalid == SDL_CONTROLLER_AXIS_INVALID);
  CHECK(gca::left_x == SDL_CONTROLLER_AXIS_LEFTX);
  CHECK(gca::left_y == SDL_CONTROLLER_AXIS_LEFTY);
  CHECK(gca::right_x == SDL_CONTROLLER_AXIS_RIGHTX);
  CHECK(gca::right_y == SDL_CONTROLLER_AXIS_RIGHTY);
  CHECK(gca::trigger_left == SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  CHECK(gca::trigger_right == SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  CHECK(gca::max == SDL_CONTROLLER_AXIS_MAX);
}

TEST_CASE("game_controller_axis operator!=", "[game_controller_axis]")
{
  using gca = game_controller_axis;

  CHECK(SDL_CONTROLLER_AXIS_INVALID != gca::right_x);
  CHECK(gca::max != SDL_CONTROLLER_AXIS_LEFTX);

  CHECK(!(SDL_CONTROLLER_AXIS_TRIGGERRIGHT != gca::trigger_right));
}
