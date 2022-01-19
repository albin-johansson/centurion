#include <gtest/gtest.h>

#include "event.hpp"

TEST(ControllerButtonEvent, Defaults)
{
  const cen::controller_button_event event;
  ASSERT_EQ(cen::event_type::controller_button_down, event.type());
}

TEST(ControllerButtonEvent, SetButton)
{
  cen::controller_button_event event;

  event.set_button(cen::ControllerButton::A);
  ASSERT_EQ(cen::ControllerButton::A, event.button());
}

TEST(ControllerButtonEvent, SetState)
{
  cen::controller_button_event event;

  event.set_state(cen::button_state::pressed);

  ASSERT_EQ(cen::button_state::pressed, event.state());
  ASSERT_TRUE(event.is_pressed());
  ASSERT_FALSE(event.is_released());

  event.set_state(cen::button_state::released);

  ASSERT_EQ(cen::button_state::released, event.state());
  ASSERT_TRUE(event.is_released());
  ASSERT_FALSE(event.is_pressed());
}

TEST(ControllerButtonEvent, SetWhich)
{
  cen::controller_button_event event;

  const SDL_JoystickID id = 7;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(ControllerButtonEvent, AsSDLEvent)
{
  const cen::controller_button_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.cbutton.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.cbutton.timestamp, event.timestamp().count());
}