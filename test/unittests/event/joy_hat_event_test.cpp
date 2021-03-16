#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyHatEvent, Defaults)
{
  cen::joy_hat_event event;
  EXPECT_GT(event.time(), 0u);
  EXPECT_EQ(cen::event_type::joystick_hat_motion, event.type());
}

TEST(JoyHatEvent, SetHat)
{
  cen::joy_hat_event event;

  constexpr auto hat = 7;
  event.set_hat(hat);

  EXPECT_EQ(hat, event.hat());
}

TEST(JoyHatEvent, SetPosition)
{
  cen::joy_hat_event event;

  constexpr auto position = cen::joy_hat_position::right;
  event.set_position(position);

  EXPECT_EQ(position, event.position());
}

TEST(JoyHatEvent, Hat)
{
  SDL_JoyHatEvent sdl;
  sdl.hat = 2;

  const cen::joy_hat_event event{sdl};
  EXPECT_EQ(sdl.hat, event.hat());
}

TEST(JoyHatEvent, Position)
{
  SDL_JoyHatEvent sdl;
  sdl.value = SDL_HAT_LEFT;

  const cen::joy_hat_event event{sdl};
  EXPECT_EQ(cen::joy_hat_position::left, event.position());
}

TEST(JoyHatEvent, AsSDLEvent)
{
  const cen::joy_hat_event event;
  const auto sdl = cen::as_sdl_event(event);

  EXPECT_EQ(sdl.jhat.type, static_cast<cen::u32>(event.type()));
  EXPECT_EQ(sdl.jhat.timestamp, event.time());
}
