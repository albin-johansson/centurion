#include <gtest/gtest.h>

#include "joystick_events.hpp"

TEST(JoyButtonEvent, Defaults)
{
  const cen::joy_button_event event;
  ASSERT_EQ(cen::event_type::joy_button_down, event.type());
}

TEST(JoyButtonEvent, SetWhich)
{
  cen::joy_button_event event;

  const SDL_JoystickID id = 92;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(JoyButtonEvent, SetButton)
{
  cen::joy_button_event event;

  const cen::uint8 button = 44;
  event.set_button(button);

  ASSERT_EQ(button, event.button());
}

TEST(JoyButtonEvent, SetState)
{
  cen::joy_button_event event;

  event.set_state(cen::button_state::pressed);

  ASSERT_EQ(cen::button_state::pressed, event.state());
  ASSERT_TRUE(event.is_pressed());
  ASSERT_FALSE(event.is_released());

  event.set_state(cen::button_state::released);

  ASSERT_EQ(cen::button_state::released, event.state());
  ASSERT_TRUE(event.is_released());
  ASSERT_FALSE(event.is_pressed());
}

TEST(JoyButtonEvent, AsSDLEvent)
{
  const cen::joy_button_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.jbutton.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.jbutton.timestamp, event.timestamp().count());
}
