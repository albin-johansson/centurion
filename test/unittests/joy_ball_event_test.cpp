#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

TEST_CASE("joy_ball_event::set_which", "[joy_ball_event]")
{
  ctn::joy_ball_event event;

  const auto which = 3;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("joy_ball_event::set_ball", "[joy_ball_event]")
{
  ctn::joy_ball_event event;

  const auto ball = 7;
  event.set_ball(ball);

  CHECK(event.ball() == ball);
}

TEST_CASE("joy_ball_event::set_dx", "[joy_ball_event]")
{
  ctn::joy_ball_event event;

  const auto dx = 173;
  event.set_dx(dx);

  CHECK(event.dx() == dx);
}

TEST_CASE("joy_ball_event::set_dy", "[joy_ball_event]")
{
  ctn::joy_ball_event event;

  const auto dy = -57;
  event.set_dy(dy);

  CHECK(event.dy() == dy);
}

TEST_CASE("joy_ball_event::which", "[joy_ball_event]")
{
  SDL_JoyBallEvent sdlEvent;
  sdlEvent.which = 5;

  ctn::joy_ball_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("joy_ball_event::ball", "[joy_ball_event]")
{
  SDL_JoyBallEvent sdlEvent;
  sdlEvent.ball = 17;

  ctn::joy_ball_event event{sdlEvent};

  CHECK(event.ball() == sdlEvent.ball);
}

TEST_CASE("joy_ball_event::dx", "[joy_ball_event]")
{
  SDL_JoyBallEvent sdlEvent;
  sdlEvent.xrel = 723;

  ctn::joy_ball_event event{sdlEvent};

  CHECK(event.dx() == sdlEvent.xrel);
}

TEST_CASE("joy_ball_event::dy", "[joy_ball_event]")
{
  SDL_JoyBallEvent sdlEvent;
  sdlEvent.yrel = 5933;

  ctn::joy_ball_event event{sdlEvent};

  CHECK(event.dy() == sdlEvent.yrel);
}
