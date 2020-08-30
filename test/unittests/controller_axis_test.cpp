#include <catch.hpp>

#include "cen.hpp"
#include "controller.hpp"

TEST_CASE("controller_axis operator==", "[controller_axis]")
{
  CHECK(SDL_CONTROLLER_AXIS_INVALID == cen::controller_axis::invalid);
  CHECK(SDL_CONTROLLER_AXIS_LEFTX == cen::controller_axis::left_x);
  CHECK(SDL_CONTROLLER_AXIS_LEFTY == cen::controller_axis::left_y);
  CHECK(SDL_CONTROLLER_AXIS_RIGHTX == cen::controller_axis::right_x);
  CHECK(SDL_CONTROLLER_AXIS_RIGHTY == cen::controller_axis::right_y);
  CHECK(SDL_CONTROLLER_AXIS_TRIGGERLEFT == cen::controller_axis::trigger_left);
  CHECK(SDL_CONTROLLER_AXIS_TRIGGERRIGHT ==
        cen::controller_axis::trigger_right);
  CHECK(SDL_CONTROLLER_AXIS_MAX == cen::controller_axis::max);

  CHECK(cen::controller_axis::invalid == SDL_CONTROLLER_AXIS_INVALID);
  CHECK(cen::controller_axis::left_x == SDL_CONTROLLER_AXIS_LEFTX);
  CHECK(cen::controller_axis::left_y == SDL_CONTROLLER_AXIS_LEFTY);
  CHECK(cen::controller_axis::right_x == SDL_CONTROLLER_AXIS_RIGHTX);
  CHECK(cen::controller_axis::right_y == SDL_CONTROLLER_AXIS_RIGHTY);
  CHECK(cen::controller_axis::trigger_left == SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  CHECK(cen::controller_axis::trigger_right ==
        SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  CHECK(cen::controller_axis::max == SDL_CONTROLLER_AXIS_MAX);
}

TEST_CASE("controller_axis operator!=", "[controller_axis]")
{
  CHECK(SDL_CONTROLLER_AXIS_INVALID != cen::controller_axis::right_x);
  CHECK(cen::controller_axis::max != SDL_CONTROLLER_AXIS_LEFTX);

  CHECK(!(SDL_CONTROLLER_AXIS_TRIGGERRIGHT !=
          cen::controller_axis::trigger_right));
}
