#include <catch.hpp>

#include "game_controller.hpp"

using namespace centurion;

TEST_CASE("game_controller_button operator==", "[game_controller_button]")
{
  using button = game_controller_button;

  CHECK(button::invalid == SDL_CONTROLLER_BUTTON_INVALID);
  CHECK(button::a == SDL_CONTROLLER_BUTTON_A);
  CHECK(button::b == SDL_CONTROLLER_BUTTON_B);
  CHECK(button::x == SDL_CONTROLLER_BUTTON_X);
  CHECK(button::y == SDL_CONTROLLER_BUTTON_Y);
  CHECK(button::back == SDL_CONTROLLER_BUTTON_BACK);
  CHECK(button::guide == SDL_CONTROLLER_BUTTON_GUIDE);
  CHECK(button::start == SDL_CONTROLLER_BUTTON_START);
  CHECK(button::left_stick == SDL_CONTROLLER_BUTTON_LEFTSTICK);
  CHECK(button::right_stick == SDL_CONTROLLER_BUTTON_RIGHTSTICK);
  CHECK(button::left_shoulder == SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
  CHECK(button::right_shoulder == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
  CHECK(button::dpad_up == SDL_CONTROLLER_BUTTON_DPAD_UP);
  CHECK(button::dpad_down == SDL_CONTROLLER_BUTTON_DPAD_DOWN);
  CHECK(button::dpad_left == SDL_CONTROLLER_BUTTON_DPAD_LEFT);
  CHECK(button::dpad_right == SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
  CHECK(button::max == SDL_CONTROLLER_BUTTON_MAX);

  CHECK(SDL_CONTROLLER_BUTTON_INVALID == button::invalid);
  CHECK(SDL_CONTROLLER_BUTTON_A == button::a);
  CHECK(SDL_CONTROLLER_BUTTON_B == button::b);
  CHECK(SDL_CONTROLLER_BUTTON_X == button::x);
  CHECK(SDL_CONTROLLER_BUTTON_Y == button::y);
  CHECK(SDL_CONTROLLER_BUTTON_BACK == button::back);
  CHECK(SDL_CONTROLLER_BUTTON_GUIDE == button::guide);
  CHECK(SDL_CONTROLLER_BUTTON_START == button::start);
  CHECK(SDL_CONTROLLER_BUTTON_LEFTSTICK == button::left_stick);
  CHECK(SDL_CONTROLLER_BUTTON_RIGHTSTICK == button::right_stick);
  CHECK(SDL_CONTROLLER_BUTTON_LEFTSHOULDER == button::left_shoulder);
  CHECK(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER == button::right_shoulder);
  CHECK(SDL_CONTROLLER_BUTTON_DPAD_UP == button::dpad_up);
  CHECK(SDL_CONTROLLER_BUTTON_DPAD_DOWN == button::dpad_down);
  CHECK(SDL_CONTROLLER_BUTTON_DPAD_LEFT == button::dpad_left);
  CHECK(SDL_CONTROLLER_BUTTON_DPAD_RIGHT == button::dpad_right);
  CHECK(SDL_CONTROLLER_BUTTON_MAX == button::max);
}

TEST_CASE("game_controller_button operator!=", "[game_controller_button]")
{
  using button = game_controller_button;

  CHECK(button::dpad_right != SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
  CHECK(SDL_CONTROLLER_BUTTON_X != button::a);

  CHECK(!(SDL_CONTROLLER_BUTTON_INVALID != button::invalid));
}