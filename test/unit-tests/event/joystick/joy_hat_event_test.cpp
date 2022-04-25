#include <gtest/gtest.h>

#include "centurion/joystick_events.hpp"

TEST(JoyHatEvent, Defaults)
{
  const cen::joy_hat_event event;
  ASSERT_EQ(cen::event_type::joy_hat_motion, event.type());
}

TEST(JoyHatEvent, SetHat)
{
  cen::joy_hat_event event;

  const cen::uint8 hat = 7;
  event.set_hat(hat);

  ASSERT_EQ(hat, event.hat());
}

TEST(JoyHatEvent, SetPosition)
{
  cen::joy_hat_event event;

  event.set_position(cen::joy_hat_position::right);
  ASSERT_EQ(cen::joy_hat_position::right, event.position());
}

TEST(JoyHatEvent, AsSDLEvent)
{
  const cen::joy_hat_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.jhat.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.jhat.timestamp, event.timestamp().count());
}
