#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyButtonEvent, Defaults)
{
  cen::joy_button_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::joystick_button_down, event.type());
}

TEST(JoyButtonEvent, SetWhich)
{
  cen::joy_button_event event;

  constexpr auto which = 92;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(JoyButtonEvent, SetButton)
{
  cen::joy_button_event event;

  constexpr auto button = 44;
  event.set_button(button);

  ASSERT_EQ(button, event.button());
}

TEST(JoyButtonEvent, SetState)
{
  cen::joy_button_event event;

  constexpr auto state = cen::button_state::pressed;
  event.set_state(state);

  ASSERT_EQ(state, event.state());
}

TEST(JoyButtonEvent, Which)
{
  SDL_JoyButtonEvent sdl;
  sdl.which = 27;

  const cen::joy_button_event event{sdl};
  ASSERT_EQ(sdl.which, event.which());
}

TEST(JoyButtonEvent, Button)
{
  SDL_JoyButtonEvent sdl;
  sdl.button = 99;

  const cen::joy_button_event event{sdl};
  ASSERT_EQ(sdl.button, event.button());
}

TEST(JoyButtonEvent, State)
{
  SDL_JoyButtonEvent sdl;
  sdl.state = SDL_RELEASED;

  const cen::joy_button_event event{sdl};
  ASSERT_EQ(cen::button_state::released, event.state());
}

TEST(JoyButtonEvent, Pressed)
{
  SDL_JoyButtonEvent sdl;
  sdl.state = SDL_PRESSED;

  const cen::joy_button_event event{sdl};
  ASSERT_TRUE(event.pressed());
}

TEST(JoyButtonEvent, Released)
{
  SDL_JoyButtonEvent sdl;
  sdl.state = SDL_RELEASED;

  const cen::joy_button_event event{sdl};
  ASSERT_TRUE(event.released());
}

TEST(JoyButtonEvent, AsSDLEvent)
{
  const cen::joy_button_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.jbutton.type, cen::ToUnderlying(event.type()));
  ASSERT_EQ(sdl.jbutton.timestamp, event.time());
}
