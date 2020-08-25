#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "controller.hpp"

TEST_CASE("controller_axis operator==", "[controller_axis]")
{
  CHECK(SDL_CONTROLLER_AXIS_INVALID == ctn::controller_axis::invalid);
  CHECK(SDL_CONTROLLER_AXIS_LEFTX == ctn::controller_axis::left_x);
  CHECK(SDL_CONTROLLER_AXIS_LEFTY == ctn::controller_axis::left_y);
  CHECK(SDL_CONTROLLER_AXIS_RIGHTX == ctn::controller_axis::right_x);
  CHECK(SDL_CONTROLLER_AXIS_RIGHTY == ctn::controller_axis::right_y);
  CHECK(SDL_CONTROLLER_AXIS_TRIGGERLEFT == ctn::controller_axis::trigger_left);
  CHECK(SDL_CONTROLLER_AXIS_TRIGGERRIGHT ==
        ctn::controller_axis::trigger_right);
  CHECK(SDL_CONTROLLER_AXIS_MAX == ctn::controller_axis::max);

  CHECK(ctn::controller_axis::invalid == SDL_CONTROLLER_AXIS_INVALID);
  CHECK(ctn::controller_axis::left_x == SDL_CONTROLLER_AXIS_LEFTX);
  CHECK(ctn::controller_axis::left_y == SDL_CONTROLLER_AXIS_LEFTY);
  CHECK(ctn::controller_axis::right_x == SDL_CONTROLLER_AXIS_RIGHTX);
  CHECK(ctn::controller_axis::right_y == SDL_CONTROLLER_AXIS_RIGHTY);
  CHECK(ctn::controller_axis::trigger_left == SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  CHECK(ctn::controller_axis::trigger_right ==
        SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  CHECK(ctn::controller_axis::max == SDL_CONTROLLER_AXIS_MAX);
}

TEST_CASE("controller_axis operator!=", "[controller_axis]")
{
  CHECK(SDL_CONTROLLER_AXIS_INVALID != ctn::controller_axis::right_x);
  CHECK(ctn::controller_axis::max != SDL_CONTROLLER_AXIS_LEFTX);

  CHECK(!(SDL_CONTROLLER_AXIS_TRIGGERRIGHT !=
          ctn::controller_axis::trigger_right));
}
