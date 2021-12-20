#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyButtonEvent, Defaults)
{
  cen::joy_button_event event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::JoyButtonDown, event.GetType());
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

  constexpr auto state = cen::ButtonState::Pressed;
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
  ASSERT_EQ(cen::ButtonState::Released, event.state());
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
  const auto sdl = cen::AsSDLEvent(event);

  ASSERT_EQ(sdl.jbutton.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(sdl.jbutton.timestamp, event.GetTimestamp());
}
