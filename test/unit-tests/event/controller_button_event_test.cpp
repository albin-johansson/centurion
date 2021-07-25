#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(ControllerButtonEvent, Defaults)
{
  cen::controller_button_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::controller_button_down, event.type());
}

TEST(ControllerButtonEvent, Constructors)
{
  ASSERT_NO_THROW(cen::controller_button_event{});

  SDL_ControllerButtonEvent e;
  ASSERT_NO_THROW(cen::controller_button_event{e});
}

TEST(ControllerButtonEvent, SetButton)
{
  cen::controller_button_event event;

  constexpr auto button = cen::controller_button::a;
  event.set_button(button);

  ASSERT_EQ(button, event.button());
}

TEST(ControllerButtonEvent, SetState)
{
  cen::controller_button_event event;

  constexpr auto state = cen::button_state::pressed;
  event.set_state(state);

  ASSERT_EQ(state, event.state());
}

TEST(ControllerButtonEvent, SetWhich)
{
  cen::controller_button_event event;

  constexpr auto which = 7;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(ControllerButtonEvent, Button)
{
  SDL_ControllerButtonEvent sdl;
  sdl.button = SDL_CONTROLLER_BUTTON_A;

  const cen::controller_button_event event{sdl};
  ASSERT_EQ(cen::controller_button::a, event.button());
}

TEST(ControllerButtonEvent, State)
{
  SDL_ControllerButtonEvent sdl;
  sdl.state = SDL_RELEASED;

  const cen::controller_button_event event{sdl};
  ASSERT_EQ(cen::button_state::released, event.state());
}

TEST(ControllerButtonEvent, Released)
{
  SDL_ControllerButtonEvent sdl;
  sdl.state = SDL_RELEASED;

  const cen::controller_button_event event{sdl};
  ASSERT_TRUE(event.released());
  ASSERT_FALSE(event.pressed());
}

TEST(ControllerButtonEvent, Pressed)
{
  SDL_ControllerButtonEvent sdl;
  sdl.state = SDL_PRESSED;

  const cen::controller_button_event event{sdl};
  ASSERT_TRUE(event.pressed());
  ASSERT_FALSE(event.released());
}

TEST(ControllerButtonEvent, Which)
{
  SDL_ControllerButtonEvent sdl;
  sdl.which = 16;

  const cen::controller_button_event event{sdl};
  ASSERT_EQ(16, event.which());
}

TEST(ControllerButtonEvent, AsSDLEvent)
{
  const cen::controller_button_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.cbutton.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.cbutton.timestamp, event.time());
}