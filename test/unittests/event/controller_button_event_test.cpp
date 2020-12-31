#include <gtest/gtest.h>

#include "event.hpp"

TEST(ControllerButtonEvent, Constructors)
{
  EXPECT_NO_THROW(cen::controller_button_event{});

  SDL_ControllerButtonEvent e;
  EXPECT_NO_THROW(cen::controller_button_event{e});
}

TEST(ControllerButtonEvent, SetButton)
{
  cen::controller_button_event event;

  constexpr auto button = cen::controller_button::a;
  event.set_button(button);

  EXPECT_EQ(button, event.button());
}

TEST(ControllerButtonEvent, SetState)
{
  cen::controller_button_event event;

  constexpr auto state = cen::button_state::pressed;
  event.set_state(state);

  EXPECT_EQ(state, event.state());
}

TEST(ControllerButtonEvent, SetWhich)
{
  cen::controller_button_event event;

  constexpr auto which = 7;
  event.set_which(which);

  EXPECT_EQ(which, event.which());
}

TEST(ControllerButtonEvent, Button)
{
  SDL_ControllerButtonEvent sdl;
  sdl.button = SDL_CONTROLLER_BUTTON_A;

  const cen::controller_button_event event{sdl};
  EXPECT_EQ(cen::controller_button::a, event.button());
}

TEST(ControllerButtonEvent, State)
{
  SDL_ControllerButtonEvent sdl;
  sdl.state = SDL_RELEASED;

  const cen::controller_button_event event{sdl};
  EXPECT_EQ(cen::button_state::released, event.state());
}

TEST(ControllerButtonEvent, Released)
{
  SDL_ControllerButtonEvent sdl;
  sdl.state = SDL_RELEASED;

  const cen::controller_button_event event{sdl};
  EXPECT_TRUE(event.released());
  EXPECT_FALSE(event.pressed());
}

TEST(ControllerButtonEvent, Pressed)
{
  SDL_ControllerButtonEvent sdl;
  sdl.state = SDL_PRESSED;

  const cen::controller_button_event event{sdl};
  EXPECT_TRUE(event.pressed());
  EXPECT_FALSE(event.released());
}

TEST(ControllerButtonEvent, Which)
{
  SDL_ControllerButtonEvent sdl;
  sdl.which = 16;

  const cen::controller_button_event event{sdl};
  EXPECT_EQ(16, event.which());
}
